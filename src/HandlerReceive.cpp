#include "HandlerReceive.hpp"
#include "Command.hpp"
#include "Server.hpp"
#include "commands/Nick.hpp"
#include <cstddef>
#include <vector>
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
		if (!cmd.empty())
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
	std::vector<std::string> know_cmds_name;
	know_cmds_name.push_back("NICK");
	know_cmds_name.push_back("PASS");

	std::vector<std::string> params;
	params.push_back("name1");
	params.push_back("name2");

	std::vector<Command*> cmds;

	for (size_t i = 0; i < _full_cmds.size(); i++)
	{
		for (size_t j = 0; j < know_cmds_name.size(); j++)
		{
			if (_full_cmds[i].compare(0, know_cmds_name[j].length(), know_cmds_name[j]) == 0)
			{
				if (j == 0)
				{
					Nick* n = new Nick(_server, _client, "test", params);
					cmds.push_back(n);
				}
			}

		}
	}

	for (size_t i = 0; i < cmds.size(); i++)
	{
		cmds.at(i)->enactCommand();
		std::cout << _client.getNickname() << "\n";
	}
}

HandlerReceive::HandlerReceive(Client& client, Server& server) : _client(client), _server(server)
{}

HandlerReceive::~HandlerReceive(void)
{}
