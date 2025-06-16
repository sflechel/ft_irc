/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sflechel <sflechel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 13:44:04 by sflechel          #+#    #+#             */
/*   Updated: 2025/06/16 17:55:20 by sflechel         ###   ########.fr       */
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
#include <iostream>


Server::Server(int port) : m_port(port)
{
	struct addrinfo	hints = {};
	struct addrinfo	*server_info, *iter;
	int				sockfd;
	int				yes = 1;

	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;

	(void)port;
	(void)m_port;
	if (getaddrinfo(NULL, "5000", &hints, &server_info) != 0)//TODO fix port/service TODO be more error specific
		throw std::runtime_error("could not get addr info");

	for (iter = server_info ; iter != NULL ; iter = iter->ai_next)
	{
		if ((sockfd = socket(iter->ai_family, iter->ai_socktype, iter->ai_protocol)) == -1)
			continue ;//TODO add error printing with strerror
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

	struct	sockaddr_storage	their_addr;
	socklen_t	addr_size = sizeof(their_addr);
	std::cerr << "waiting for a connection..." << std::endl;
	while (1)
	{
		int new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &addr_size);
		if (new_fd == -1)
			continue ;
		else
			std::cerr << "server connected to client!" << std::endl;
	}
}

Server::~Server()
{
	close(m_master_socket);
}
