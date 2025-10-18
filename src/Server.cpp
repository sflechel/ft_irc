#include "Server.hpp"
#include <asm-generic/socket.h>
#include <cstddef>
#include <map>
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
#include "Client.hpp"
#include "HandlerConnection.hpp"
#include "HandlerReceive.hpp"
#include "HandlerRespond.hpp"

void	Server::poll_events()
{
	struct epoll_event	events[MAX_EVENTS];
	int					nb_fds;

	while (true)
	{
		nb_fds = epoll_wait(_epollfd, events, MAX_EVENTS, 0);
		if (nb_fds == -1)
			throw std::runtime_error("epoll failed");

		for (int i = 0 ; i < nb_fds ; i++)
		{
			if (events[i].data.fd == _master_socket)
			{
				HandlerConnection hconn = HandlerConnection(_master_socket);
				Client*	newClient = hconn.acceptConnection();
                hconn.registerClient(newClient, this->_new_clients, this->_epollfd);
			}
			else if (events[i].events & EPOLLIN)
			{
				HandlerReceive	hrecv = HandlerReceive(*(Client *)(events[i].data.ptr), *this);
				hrecv.readClientRequest();
                hrecv.splitResponseToCmds();
                hrecv.execCmds();
			}
			else if (events[i].events & EPOLLOUT)
			{
                HandlerRespond  hresp = HandlerRespond(*(Client *)(events[i].data.ptr));
                hresp.respond();
            }
			else
				throw std::runtime_error("how did we get here?");
		}
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

void	Server::setup_master_socket(char *port)
{
	struct addrinfo	hints = {};
	struct addrinfo	*server_info, *iter;
	int				sockfd;
	int				yes = 1;

	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;

	if (getaddrinfo(NULL, port, &hints, &server_info) != 0)//TODO fix port/service TODO be more error specific
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
	this->_master_socket_address = *(struct sockaddr_in *)iter;//TODO fix casts
	this->_master_socket_address_len = iter->ai_addrlen;
	this->_master_socket = sockfd;

	if (listen(_master_socket, LISTEN_BACKLOG) == -1)
		throw std::runtime_error("failed to listen");
	if (fcntl(_master_socket, F_SETFL, O_NONBLOCK) == -1)
		throw  std::runtime_error("failed to change socket to non-blocking");
}

Server::Server(char *port, char *password) : _name("IrcTestServer")
{
	_password = std::string(password);

	setup_master_socket(port);
	setup_poll();
	poll_events();
}

void    Server::removeNewClient(int index)
{
    std::vector<Client*>::iterator   it;

    it = _new_clients.begin() + index;
    delete _new_clients.at(index);
    _new_clients.erase(it);
}

void    Server::removeClient(std::string nickname)
{
    delete _clients.at(nickname);
    _clients.erase(nickname);
}

void    Server::registerClient(Client* client, std::string nickname)
{
        std::pair<std::string, Client*> pair(nickname, client);
        client->setNickname(nickname);
        this->removeNewClient(std::distance(*_new_clients.data(), client));
        _clients.insert(pair);
}

void    Server::updateNickname(Client* client, std::string new_nickname)
{
    _clients.erase(client->getNickname());
    client->setNickname(new_nickname);
    std::pair<std::string, Client*> pair(new_nickname, client);
    _clients.insert(pair);
}

Server::~Server()
{
    for (size_t i = 0 ; i < _new_clients.size() ; i++)
    {
        delete _new_clients.at(i);
    }
    for (std::map<std::string, Client*>::iterator it = _clients.begin(); it != _clients.end(); it++)
    {
        delete it->second;
    }
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
    Client* client;
    try {client = _clients.at(nickname);}
    catch (std::out_of_range)
    {
        return NULL;
    }
    return client;
}

std::vector<Channel>&    Server::getChannels(void)
{
    return _channels;
}

std::vector<Client*>&    Server::getNewClients(void)
{
    return (_new_clients);
}
