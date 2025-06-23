/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Handler_receive.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edarnand <edarnand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 16:56:49 by sflechel          #+#    #+#             */
/*   Updated: 2025/06/23 18:52:04 by edarnand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Handler_receive.hpp"
#include <algorithm>
#include <cerrno>
#include <sys/socket.h>
#include <iostream>
#include <sstream>

void	Handler_receive::handle_cmd(std::string msg)
{
	std::cout << "and receve a CMD:\n" << msg << std::endl;
}

void	Handler_receive::handle_client_msg(std::string msg)
{
	if (msg[0] == '\0')
		return ;
	else if (msg[0] == '/')
		return (handle_cmd(msg));
	else
	 	std::cout << "and receve a message:\n" << msg << std::endl;
}

void	Handler_receive::read_data_sent()
{
	static std::string	message;
	char				read_buffer[READ_BUFFER_SIZE + 1];
	int					bytes_read = READ_BUFFER_SIZE;
	int					client_fd = this->m_client.get_my_fd();

	std::cout << "server read ";
	read_buffer[0] = 0;
	while (bytes_read == READ_BUFFER_SIZE)
	{
		bytes_read = recv(client_fd, read_buffer, READ_BUFFER_SIZE, 0);
		if (bytes_read <= 0)
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
			break ;
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
