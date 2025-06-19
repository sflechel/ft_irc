/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sflechel <sflechel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 13:44:04 by sflechel          #+#    #+#             */
/*   Updated: 2025/06/19 18:07:58 by sflechel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"
#include <asm-generic/socket.h>
#include <stdexcept>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <fcntl.h>
#include <sys/epoll.h>
#include "Handler_connection.hpp"
#include "Handler_receive.hpp"

void	Server::poll_events()
{
	struct epoll_event	events[MAX_EVENTS], poll_opts;
	int					nb_fds;

	while (true)
	{
		nb_fds = epoll_wait(this->m_epollfd, events, MAX_EVENTS, -1);
		if (nb_fds == -1)
			throw std::runtime_error("epoll failed");

		for (int i = 0 ; i < nb_fds ; i++)
		{
			if (events[i].data.fd == this->m_master_socket)
			{
				Handler_connection hconn = Handler_connection(this->m_master_socket);
				Client	new_client = hconn.accept_connection();
				this->m_clients.push_back(new_client);
				poll_opts.events = EPOLLIN | EPOLLOUT | EPOLLET;
				int conn_fd = new_client.get_my_fd();
				poll_opts.data.fd = conn_fd;
				poll_opts.data.ptr = &new_client;
				if (epoll_ctl(this->m_epollfd, EPOLL_CTL_ADD, conn_fd, &poll_opts) == -1)
					throw std::runtime_error("failed to add connection to epoll");
			}
			else if (events[i].events & EPOLLIN)
			{
				Handler_receive	hrecv = Handler_receive(*(Client *)(events[i].data.ptr));
				hrecv.read_data_sent();
			}
			else if (events[i].events & EPOLLOUT)
			{}
			else
				throw std::runtime_error("how did we get here?");
		}
	}
}

void Server::setup_poll()
{
	struct epoll_event	poll_opts;

	m_epollfd = epoll_create(1);
	if (this->m_epollfd == -1)
		throw std::runtime_error("failed to initialize epoll");
	poll_opts.events = EPOLLIN;
	poll_opts.data.fd = this->m_master_socket;
	if (epoll_ctl(this->m_epollfd, EPOLL_CTL_ADD, this->m_master_socket, &poll_opts) == -1)
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
	this->m_master_socket_address = *(struct sockaddr_in *)iter;//TODO fix casts
	this->m_master_socket_address_len = iter->ai_addrlen;
	this->m_master_socket = sockfd;

	if (listen(m_master_socket, LISTEN_BACKLOG) == -1)
		throw std::runtime_error("failed to listen");
	if (fcntl(m_master_socket, F_SETFL, O_NONBLOCK) == -1)
		throw  std::runtime_error("failed to change socket to non-blocking");
}

Server::Server(char *port, char *password)
{
	m_password = std::string(password);

	setup_master_socket(port);
	setup_poll();
	poll_events();
}

Server::~Server()
{
	for (size_t i = 0 ; i >= this->m_clients.size() ; i++)
		close(this->m_clients[i].get_my_fd());
	close(m_master_socket);
	close(m_epollfd);
}
