#include "Server.hpp"
#include <stdexcept>
#include <sys/epoll.h>
#include "HandlerConnection.hpp"
#include "HandlerReceive.hpp"
#include "HandlerRespond.hpp"
#include <csignal>

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
