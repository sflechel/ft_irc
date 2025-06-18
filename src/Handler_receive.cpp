/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Handler_receive.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sflechel <sflechel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 16:56:49 by sflechel          #+#    #+#             */
/*   Updated: 2025/06/18 09:17:59 by sflechel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Handler_receive.hpp"
#include <sys/socket.h>
#include <iostream>

void	Handler_receive::read_data_sent()
{
	char	read_buffer[READ_BUFFER_SIZE];
	int		bytes_read = READ_BUFFER_SIZE;

	std::cout << "Message received!" << std::endl;
	while (bytes_read == READ_BUFFER_SIZE)
	{
		bytes_read = recv(this->m_sock_fd, read_buffer, READ_BUFFER_SIZE, 0);
		std::string message(read_buffer);
		std::cout << message;
	}
	std::cout << std::endl;
}

Handler_receive::Handler_receive(int sock_fd) : m_sock_fd(sock_fd)
{
}

Handler_receive::~Handler_receive()
{}
