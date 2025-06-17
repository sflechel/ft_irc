/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Reactor.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sflechel <sflechel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 10:24:56 by sflechel          #+#    #+#             */
/*   Updated: 2025/06/17 16:44:51 by sflechel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Reactor.hpp"
#include <stdexcept>
#include <sys/epoll.h>
#include "Handler_connection.hpp"

void	Reactor::polling_loop()
{
	struct epoll_event	poll_opts;
	int	nb_fds;

	while (true)
	{
		nb_fds = epoll_wait(this->m_epollfd, this->m_events, MAX_EVENTS, -1);
		if (nb_fds == -1)
			throw std::runtime_error("epoll failed");

		for (int n = 0 ; n < nb_fds ; n++)
		{
			if (this->m_events[n].data.fd == this->m_epollfd)
			{
				Handler_connection hconn = Handler_connection(this->m_server.get_msocket_fd());
				int	conn_fd = hconn.accept_connection();
				poll_opts.events = EPOLLIN | EPOLLET;
				poll_opts.data.fd = conn_fd;
				if (epoll_ctl(this->m_epollfd, EPOLL_CTL_ADD, conn_fd, &poll_opts) == -1)
					throw std::runtime_error("failed to add connection to epoll");
			}
			else
		}
	}
}

Reactor::Reactor(Server server) : m_server(server)
{
	m_epollfd = epoll_create(0);
	if (m_epollfd == -1)
		throw std::runtime_error("failed to initialize epoll");
	m_poll_opts.events = EPOLLIN;
	m_poll_opts.data.fd = m_server.get_msocket_fd();
	if (epoll_ctl(m_epollfd, EPOLL_CTL_ADD, m_server.get_msocket_fd(), &m_poll_opts) == -1)
		throw std::runtime_error("failed to parametrize epoll");
}
