/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Reactor.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sflechel <sflechel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 10:24:56 by sflechel          #+#    #+#             */
/*   Updated: 2025/06/18 09:17:44 by sflechel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Reactor.hpp"
#include "Handler_connection.hpp"
#include "Handler_receive.hpp"
#include <iostream>
#include <stdexcept>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <unistd.h>

void	Reactor::polling_loop()
{
	struct epoll_event	poll_opts;
	int					nb_fds;

	while (true)
	{
		std::cout << "reached main loop" << std::endl;


		nb_fds = epoll_wait(this->m_epollfd, this->m_events, MAX_EVENTS, -1);
		if (nb_fds == -1)
			throw std::runtime_error("epoll failed");

		for (int i = 0 ; i < nb_fds ; i++)
		{
			if (this->m_events[i].data.fd == this->m_epollfd)
			{
				Handler_connection hconn = Handler_connection(this->m_server.get_msocket_fd());
				int	conn_fd = hconn.accept_connection();
				poll_opts.events = EPOLLIN | EPOLLOUT | EPOLLET;
				poll_opts.data.fd = conn_fd;
				if (epoll_ctl(this->m_epollfd, EPOLL_CTL_ADD, conn_fd, &poll_opts) == -1)
					throw std::runtime_error("failed to add connection to epoll");
			}
			else
			{
				Handler_receive	hrecv = Handler_receive(this->m_events[i].data.fd);
				hrecv.read_data_sent();
			}
		}
	}
}

Reactor::Reactor(Server server) : m_server(server)
{
	m_epollfd = epoll_create(1);
	if (m_epollfd == -1)
		throw std::runtime_error("failed to initialize epoll");
	m_poll_opts.events = EPOLLIN;
	m_poll_opts.data.fd = m_server.get_msocket_fd();
	if (epoll_ctl(m_epollfd, EPOLL_CTL_ADD, m_server.get_msocket_fd(), &m_poll_opts) == -1)
		throw std::runtime_error("failed to parametrize epoll");

	struct epoll_event	poll_opts;
	int					nb_fds;

	while (true)
	{
		nb_fds = epoll_wait(this->m_epollfd, this->m_events, MAX_EVENTS, -1);
		if (nb_fds == -1)
			throw std::runtime_error("epoll failed");

		for (int i = 0 ; i < nb_fds ; i++)
		{
			if (this->m_events[i].data.fd == this->m_server.get_msocket_fd())
			{
				Handler_connection hconn = Handler_connection(this->m_server.get_msocket_fd());
				int	conn_fd = hconn.accept_connection();
				poll_opts.events = EPOLLIN | EPOLLOUT | EPOLLET;
				poll_opts.data.fd = conn_fd;
				if (epoll_ctl(this->m_epollfd, EPOLL_CTL_ADD, conn_fd, &poll_opts) == -1)
					throw std::runtime_error("failed to add connection to epoll");
			}
			else
			{
				Handler_receive	hrecv = Handler_receive(this->m_events[i].data.fd);
				hrecv.read_data_sent();
			}
		}
	}
}

Reactor::~Reactor()
{
	close(this->m_epollfd);
}
