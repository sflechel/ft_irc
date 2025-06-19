/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Handler_receive.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edarnand <edarnand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 16:56:49 by sflechel          #+#    #+#             */
/*   Updated: 2025/06/19 17:47:07 by sflechel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Handler_receive.hpp"
#include <sys/socket.h>
#include <iostream>

void	Handler_receive::read_data_sent()
{
	char	read_buffer[READ_BUFFER_SIZE + 1];
	int		bytes_read = READ_BUFFER_SIZE;
	int		client_fd = this->m_client.get_my_fd();

	std::cout << "Message received!" << std::endl;
	read_buffer[0] = 0;
	while (bytes_read == READ_BUFFER_SIZE)
	{
		bytes_read = recv(client_fd, read_buffer, READ_BUFFER_SIZE, 0);
		read_buffer[bytes_read] = 0;
		std::string message(read_buffer);
		std::cout << message;
	}
}

Handler_receive::Handler_receive(Client client) : m_client(client)
{
}

Handler_receive::~Handler_receive()
{}
