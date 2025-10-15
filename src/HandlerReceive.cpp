#include "HandlerReceive.hpp"
#include "Server.hpp"
#include <iostream>

void HandlerReceive::readClientRequest()
{
	std::string new_request;
	char read_buffer[READ_BUFFER_SIZE + 1];
	int bytes_read = READ_BUFFER_SIZE;
	int client_fd = _client.getFd();

	read_buffer[0] = 0;
	while (bytes_read == READ_BUFFER_SIZE)
	{
		bytes_read = recv(client_fd, read_buffer, READ_BUFFER_SIZE, 0);
		if (bytes_read < 0)
		{
			std::cout << "recv fail\n";
			break ;
		}
		if (bytes_read == 0)
		{
			std::cout << "recv read empty\n";
			break ;
		}
		read_buffer[bytes_read] = 0;
		new_request += read_buffer;
	}
	_client.setRequest(_client.getRequest() + new_request);
}

void	HandlerReceive::splitResponseToCmds(void)
{
	std::string full_request = _client.getRequest();
	size_t cmd_start = 0;
	size_t cmd_end;

	cmd_end = full_request.find("\r\n", cmd_start);
	while (cmd_end != std::string::npos)
	{
		std::string cmd = full_request.substr(cmd_start, cmd_end - cmd_start);
		std::cout << "cmd:" << cmd << "\n";
		_full_cmds.push_back(cmd);
		cmd_start = cmd_end + 2;
		cmd_end = full_request.find("\r\n", cmd_start);
	}
	if (cmd_start != 0)
		_client.setRequest(full_request.substr(cmd_start, std::string::npos));
	(void)_server;
}

void	HandlerReceive::execCmds(void)
{
	for (size_t i = 0; i < _full_cmds.size(); i++)
	{
		//Command cmd(_full_cmds[i]);



		//if (cmd.is_valid_cmd())
		//{
		//	cmd.parse_cmd();
		//	std::string test = ":a 403 edarnand :test dsf sf d\r\n";
		//	write(client_fd, test.c_str(), test.size());
		//	//write(0, "PRIVMSG edarnand :asdadsasd\r\n", 30);
		//}
	}
}

HandlerReceive::HandlerReceive(Client& client, Server& server) : _client(client), _server(server)
{}

HandlerReceive::~HandlerReceive(void)
{}
