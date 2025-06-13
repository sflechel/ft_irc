/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sflechel <sflechel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 13:44:04 by sflechel          #+#    #+#             */
/*   Updated: 2025/06/13 15:55:09 by sflechel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"
#include <stdexcept>
#include <string>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <fcntl.h>


Server::Server(std::string ip_address, int port) : m_port(port), m_ip_address(ip_address)
{
	struct addrinfo	hints = {0};
	struct addrinfo	*server_info, *iter;
	int sockfd;

	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;

	if (getaddrinfo(NULL, "5000", &hints, &server_info) != 0)//TODO fix port/service TODO be more error specific
		throw std::runtime_error("could not get addr info");

	for (iter = server_info ; iter != NULL ; iter = iter->ai_next)
	{
		if ((sockfd = socket(iter->ai_family, iter->ai_socktype, iter->ai_protocol)) == -1)
			continue ;//TODO add error printing
		if (bind(sockfd, iter->ai_addr, iter->ai_addrlen) == -1)
		{
			close(sockfd);
			continue ;
		}
		break ;
	}
	freeaddrinfo(server_info);
	if (iter == NULL)
		throw std::runtime_error("failed to find working address");
	m_master_socket_address = *(struct sockaddr_in *)iter->ai_next;//TODO fix casts
	m_master_socket_address_len = iter->ai_addrlen;
	m_master_socket = sockfd;

	if (listen(m_master_socket, LISTEN_BACKLOG) == -1)
		throw std::runtime_error("failed to listen");
	if (fcntl(m_master_socket, F_SETFL, O_NONBLOCK) == -1)
		throw  std::runtime_error("failed to change socket to non-blocking");
}

Server::~Server()
{
	close(m_master_socket);
}
