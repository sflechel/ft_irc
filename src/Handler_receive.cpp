/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Handler_receive.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edarnand <edarnand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 16:56:49 by sflechel          #+#    #+#             */
/*   Updated: 2025/06/20 11:31:52 by edarnand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Handler_receive.hpp"
#include <algorithm>
#include <sys/socket.h>
#include <iostream>
#include <sstream>

void	Handler_receive::parse_client_msg(char *msg, int msg_len)
{
	if (msg[0] == '\0')
		return ;
	char *crlf = std::find(msg, msg + msg_len, '\r');
	if (!crlf || *(crlf + 1) != '\n')
		return ;//ignore empty and invalid msg

	char *first_space = std::find(msg, msg + msg_len,  ' ');
	char *cmd = msg;
	char *params;

	if (first_space)
	{
		*first_space = '\0';
		params = first_space + 1;
	}
	else
		params = NULL;

	std::cout << cmd << " | " << params;
}

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

	parse_client_msg(read_buffer, bytes_read);
}

Handler_receive::Handler_receive(Client client) : m_client(client)
{
	(void)m_sock_fd;
}

Handler_receive::~Handler_receive()
{}
