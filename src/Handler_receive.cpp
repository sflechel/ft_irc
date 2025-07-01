/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Handler_receive.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edarnand <edarnand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 16:56:49 by sflechel          #+#    #+#             */
/*   Updated: 2025/07/01 18:54:32 by edarnand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Handler_receive.hpp"
#include "Command.hpp"
#include <ostream>
#include <cerrno>
#include <sys/socket.h>
#include <iostream>

void Handler_receive::read_data_sent()
{
	std::string cmd_str;
	char read_buffer[READ_BUFFER_SIZE + 1];
	int bytes_read = READ_BUFFER_SIZE;
	int client_fd = this->m_client.get_my_fd();

	std::cout << "server read" << std::endl;
	read_buffer[0] = 0;
	while (bytes_read == READ_BUFFER_SIZE)
	{
		bytes_read = recv(client_fd, read_buffer, READ_BUFFER_SIZE, 0);
		if (bytes_read < 0)
		{
			std::cout << "recv fail" << std::endl;
			return ;
		}
		if (bytes_read == 0)
		{
			std::cout << "and a client deconnected" << std::endl;
			return ;
		}
		read_buffer[bytes_read] = 0;
		cmd_str += read_buffer;
		if (cmd_str.find("\r\n") != std::string::npos)
		{
			Command cmd(cmd_str);
			if (cmd.is_valid_cmd())
			{
				cmd.parse_cmd();
			}
			return ;
		}
		else
			std::cout << "and does not got the full message" << std::endl;
	}
}

Handler_receive::Handler_receive(Client client) : m_client(client)
{
	(void)m_sock_fd;
}

Handler_receive::~Handler_receive()
{}
