/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Handler_receive.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edarnand <edarnand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 16:56:49 by sflechel          #+#    #+#             */
/*   Updated: 2025/06/30 13:50:57 by edarnand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Handler_receive.hpp"
#include <ostream>
#include <vector>
#include <cerrno>
#include <sys/socket.h>
#include <iostream>
#include <sstream>

void Handler_receive::handle_client_msg(std::string msg)
{
	std::vector<std::string> params;
	std::string cmd;

	if (msg.compare("\r\n") == 0)
	{
		std::cout << "and receve a empty message" << std::endl;
		return ;
	}
	msg.resize(msg.size() - 2);
	std::cout << "and receve a message:\n" << msg << '\n';

	std::stringstream ss(msg);
	std::string tmp;
	while (std::getline(ss, tmp, ' '))
	{
		if (tmp[0] == ':')
		{
			params.push_back(msg.substr(msg.find(':') + 1, std::string::npos));
			break ;
		}
		else if (!tmp.empty())
			params.push_back(tmp);
	}

	for (size_t i = 0; i < params.size(); i++)
	{
		std::cout << params[i];
		if (i + 1 != params.size())
			std::cout << '|';
	}
	std::cout << std::endl;
}

void Handler_receive::read_data_sent()
{
	static std::string message;
	char read_buffer[READ_BUFFER_SIZE + 1];
	int bytes_read = READ_BUFFER_SIZE;
	int client_fd = this->m_client.get_my_fd();

	std::cout << "server read ";
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
		message += read_buffer;
		if (message.find("\r\n") != std::string::npos)
		{
			handle_client_msg(message);
			message.clear();
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
