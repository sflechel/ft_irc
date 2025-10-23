#include "Server.hpp"
#include <asm-generic/socket.h>
#include <csetjmp>
#include <cstddef>
#include <map>
#include <new>
#include <set>
#include <stdexcept>
#include <string>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <fcntl.h>
#include <sys/epoll.h>
#include <utility>
#include "Channel.hpp"
#include "Client.hpp"
#include "HandlerConnection.hpp"
#include "HandlerReceive.hpp"
#include "HandlerRespond.hpp"
#include <csignal>
#include <iostream>

extern volatile sig_atomic_t	g_signum;

void	Server::poll_events()
{
	struct epoll_event	events[MAX_EVENTS];
	int					nb_fds;

	while (g_signum != SIGINT)
	{
		nb_fds = epoll_wait(_epollfd, events, MAX_EVENTS, 5000);
		if (nb_fds == -1)
			throw std::runtime_error("epoll failed");

		for (int i = 0 ; i < nb_fds ; i++)
		{
			if (events[i].events & (EPOLLERR | EPOLLHUP))
			{
				this->forceQuitClient((Client*)events[i].data.ptr);
				continue;
			}
			if (events[i].data.fd == _master_socket)
			{
				HandlerConnection hconn = HandlerConnection(*this);
				Client*	newClient = hconn.acceptConnection();
				hconn.registerClient(newClient, _new_clients, _epollfd);
				continue;
			}
			if (events[i].events & EPOLLIN)
			{
				HandlerReceive	hrecv = HandlerReceive(*(Client*)(events[i].data.ptr), *this);
				if (hrecv.readClientRequest() <= 0)
				{
					this->forceQuitClient((Client*)events[i].data.ptr);
					continue;
				}
				hrecv.splitResponseToCmds();
				hrecv.execCmds();
			}
			if (events[i].events & EPOLLOUT)
			{
				HandlerRespond  hresp = HandlerRespond(*(Client*)(events[i].data.ptr), *this);
				hresp.respond();
			}
		}
		this->sendersToEpollOut();
	}
}

void Server::setup_poll()
{
	struct epoll_event	poll_opts;

	this->_epollfd = epoll_create(1);
	if (this->_epollfd == -1)
		throw std::runtime_error("failed to initialize epoll");
	poll_opts.events = EPOLLIN;
	poll_opts.data.fd = this->_master_socket;
	if (epoll_ctl(this->_epollfd, EPOLL_CTL_ADD, this->_master_socket, &poll_opts) == -1)
		throw std::runtime_error("failed to parametrize epoll");
}

void	Server::setup_master_socket(std::string port)
{
	struct addrinfo	hints = {};
	struct addrinfo	*server_info, *iter;
	int				sockfd;
	int				yes = 1;

	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;

	if (getaddrinfo(NULL, port.c_str(), &hints, &server_info) != 0)
		throw std::runtime_error("could not get addr info");

	for (iter = server_info ; iter != NULL ; iter = iter->ai_next)
	{
		if ((sockfd = socket(iter->ai_family, iter->ai_socktype, iter->ai_protocol)) == -1)
			continue ;
		if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1)
		{
			close(sockfd);
			continue ;
		}
		if (bind(sockfd, iter->ai_addr, iter->ai_addrlen) == -1)
		{
			close(sockfd);
			continue ;
		}
		break ;
	}
	if (iter == NULL)
	{
		freeaddrinfo(server_info);
		throw std::runtime_error("failed to find working address");
	}
	this->_master_socket_address = *(struct sockaddr_in*)iter;
	this->_master_socket_address_len = iter->ai_addrlen;
	this->_master_socket = sockfd;

	freeaddrinfo(server_info);
	if (listen(_master_socket, LISTEN_BACKLOG) == -1)
		throw std::runtime_error("failed to listen");
	if (fcntl(_master_socket, F_SETFL, O_NONBLOCK) == -1)
		throw  std::runtime_error("failed to change socket to non-blocking");
}

void	Server::sendersToEpollOut(void)
{
	struct epoll_event			poll_opts;
	std::set<Client*>::iterator	it;

	for (it = _senders.begin() ; it != _senders.end() ; it++)
	{
		Client*	client = *it;
		poll_opts.events = EPOLLIN | EPOLLOUT;
		int conn_fd = client->getFd();
		poll_opts.data.fd = conn_fd;
		poll_opts.data.ptr = client;
		if (epoll_ctl(_epollfd, EPOLL_CTL_MOD, conn_fd, &poll_opts) == -1)
			throw std::runtime_error("failed to change client fd to listening out");
	}
}

void	Server::addSender(Client* client)
{
	_senders.insert(client);
}

void	Server::removeSender(Client* client)
{
	std::set<Client*>::iterator	it = _senders.find(client);
	if (it != _senders.end())
		_senders.erase(it);
}

Server::Server(std::string port, std::string password) : _password(password), _name("IrcTestServer")
{
	setup_master_socket(port);
	setup_poll();
}

void	Server::forceQuitClient(Client* client)
{
	if (client == NULL)
		return;
	std::string	nickname = client->getNickname();
	if (nickname.empty())
		removeNewClient(client);
	else
		removeClient(nickname);
}

void	Server::removeNewClient(Client* client)
{
	std::set<Client*>::iterator   it = _new_clients.find(client);

	if (it == _new_clients.end())
		return;
	delete *it;
	_new_clients.erase(it);
	std::cout << "Client quit\n";

	it = _senders.find(client);
	if (it == _senders.end())
		return;
	_senders.erase(it);
}

void	Server::removeClient(std::string nickname)
{
	std::map<std::string, Channel*>  channels = this->getChannels();
	std::map<std::string, Channel*>::iterator   it;
	Client*	client = this->getClient(nickname);
	for (it = channels.begin() ; it != channels.end() ; it++)
	{
		if (it->second->isUserInChannel(nickname))
		{
			std::string		name = it->second->getName();
			std::string		msg = ":" + nickname + " PART " + name + "\r\n";
			client->addResponse(msg);
			it->second->sendChannelMessage(msg, *client);
		}
		it->second->leave(client->getNickname());
	}
	delete _clients.at(nickname);
	_clients.erase(nickname);
	std::cout << "Client quit\n";


	std::set<Client*>::iterator	iter = _senders.find(client);
	if (iter == _senders.end())
		return;
	_senders.erase(iter);
}

void	Server::registerClient(Client* client, std::string nickname)
{
	std::pair<std::string, Client*> pair(nickname, client);
	client->setNickname(nickname);
	std::set<Client*>::iterator it = _new_clients.find(client);
	if (it == _new_clients.end())
		return;
	_new_clients.erase(it);
	_clients.insert(pair);
}

void	Server::createChannel(std::string name, Client& user)
{
	Channel *new_channel = new Channel(*this, name, user);
	std::pair<std::string, Channel*>	pair(name, new_channel);
	_channels.insert(pair);
}

void	Server::updateNickname(Client* client, std::string new_nickname)
{
	std::string	old_nickname = client->getNickname();
	std::map<std::string, Channel*>::iterator   it;
	for (it = _channels.begin() ; it != _channels.end() ; it++)
	{
		if (it->second->isUserInChannel(old_nickname))
		{
			std::string		name = it->second->getName();
			std::string		msg = ":" + old_nickname + " NICK " + new_nickname + "\r\n";
			client->addResponse(msg);
			it->second->sendChannelMessage(msg, *client);
			it->second->updateNickname(old_nickname, new_nickname);
		}
		if (it->second->isUserInvited(old_nickname))
			it->second->updateNicknameInvited(old_nickname, new_nickname);
		it->second->leave(client->getNickname());
	}

	_clients.erase(client->getNickname());
	client->setNickname(new_nickname);
	std::pair<std::string, Client*> pair(new_nickname, client);
	_clients.insert(pair);

}

Server::~Server()
{
	for (std::set<Client*>::iterator it = _new_clients.begin() ; it != _new_clients.end() ; it++)
		delete *it;
	for (std::map<std::string, Client*>::iterator it = _clients.begin(); it != _clients.end(); it++)
		delete it->second;
	for (std::map<std::string, Channel*>::iterator it = _channels.begin(); it != _channels.end(); it++)
		delete it->second;
	close(_master_socket);
	close(_epollfd);
}

std::string Server::getPassword(void) const
{
	return (this->_password);
}

std::string Server::getName(void) const
{
	return (this->_name);
}

Client* Server::getClient(std::string nickname)
{
	std::map<std::string, Client*>::iterator it = _clients.find(nickname);
	if (it == _clients.end())
		return (NULL);
	return (it->second);
}

std::map<std::string, Channel*>&	Server::getChannels(void)
{
	return _channels;
}

Channel*	Server::getChannel(std::string name)
{
	std::map<std::string, Channel*>::iterator it = _channels.find(name);
	if (it == _channels.end())
		return (NULL);
	return (it->second);
}

std::set<Client*>&	Server::getNewClients(void)
{
	return (_new_clients);
}

int	Server::getMasterSocket(void) const
{
	return _master_socket;
}

int	Server::getEpollFd(void) const
{
	return _epollfd;
}
