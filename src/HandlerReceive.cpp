#include "HandlerReceive.hpp"
#include "Command.hpp"
#include <ostream>
#include <cerrno>
#include <sys/socket.h>
#include <iostream>
#include <unistd.h>

void HandlerReceive::read_data_sent()
{
	std::string cmd_str;
	char read_buffer[READ_BUFFER_SIZE + 1];
	int bytes_read = READ_BUFFER_SIZE;
	int client_fd = _client.get_my_fd();

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
				std::string test = ":a 403 edarnand :test dsf sf d\r\n";
				write(client_fd, test.c_str(), test.size());
				//write(0, "PRIVMSG edarnand :asdadsasd\r\n", 30);
			}
			return ;
		}
		else
			std::cout << "and does not got the full message" << std::endl;
	}
}

HandlerReceive::HandlerReceive(Client& client) : _client(client)
{}

HandlerReceive::~HandlerReceive()
{}
