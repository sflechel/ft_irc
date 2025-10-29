#include "Server.hpp"
#include <stdexcept>
#include <netdb.h>
#include <fcntl.h>
#include <sys/epoll.h>
#include <csignal>

void	Server::init(std::string port)
{
	setup_master_socket(port);
	setup_poll();
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

