/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Handler_connection.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sflechel <sflechel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 15:20:30 by sflechel          #+#    #+#             */
/*   Updated: 2025/06/17 16:33:42 by sflechel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Handler_connection.hpp"
#include <fcntl.h>
#include <stdexcept>
#include <sys/socket.h>
#include <sys/epoll.h>

Handler_connection::Handler_connection(int master_sock) : m_master_sock(master_sock)
{
}

int	Handler_connection::accept_connection()
{
	struct sockaddr	addr;
	socklen_t		len_addr;
	int				conn_fd;

	conn_fd = accept(this->m_master_sock, &addr, &len_addr);
	if (conn_fd == -1)
		throw std::runtime_error("failed to accept connection");

	if (fcntl(conn_fd, F_SETFL, O_NONBLOCK) == -1)
		throw std::runtime_error("failed to set connection socket to non blocking");

	return (conn_fd);
}
