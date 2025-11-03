#include "HandlerReceive.hpp"
#include "Command.hpp"
#include "Server.hpp"
#include "commands/Nick.hpp"
#include "commands/Pass.hpp"
#include "commands/PrivMsg.hpp"
#include "commands/Quit.hpp"
#include "commands/User.hpp"
#include "commands/Join.hpp"
#include "commands/Mode.hpp"
#include "commands/Kick.hpp"
#include "commands/UnknownCommand.hpp"
#include "commands/Topic.hpp"
#include "commands/Part.hpp"
#include "commands/Invite.hpp"
#include <cstddef>
#include <string>
#include <vector>
#include <sstream>

int HandlerReceive::readClientRequest()
{
	const unsigned int	READ_BUFFER_SIZE = 3;
	std::string new_request;
	char read_buffer[READ_BUFFER_SIZE + 1];
	int bytes_read = READ_BUFFER_SIZE;
	int client_fd = _client.getFd();
	bool	is_first_read = true;

	read_buffer[0] = 0;
	while (bytes_read == READ_BUFFER_SIZE)
	{
		bytes_read = recv(client_fd, read_buffer, READ_BUFFER_SIZE, 0);
		if (bytes_read <= 0 && is_first_read)
			return -1;
		if (bytes_read == -1 && !is_first_read)
			break;
		read_buffer[bytes_read] = 0;
		new_request += read_buffer;
		is_first_read = false;
	}
	_client.setRequest(_client.getRequest() + new_request);
	return 1;
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
		if (!cmd.empty())
			_full_cmds.push_back(cmd);
		cmd_start = cmd_end + 2;
		cmd_end = full_request.find("\r\n", cmd_start);
	}
	if (cmd_start != 0)
		_client.setRequest(full_request.substr(cmd_start, std::string::npos));
}

void	HandlerReceive::parseCmdParam(std::string &input, std::vector<std::string>& vec)
{
	if (input.find(':') == 0)
	{
		size_t first_space = input.find(' ');
		if (first_space == std::string::npos)
			return ;
		input = input.substr(first_space + 1, std::string::npos);
	}

	std::string last_param;
	bool		has_last_param = false;
	size_t		colon_pos = input.find(':');
	if (colon_pos != std::string::npos)
	{
		last_param = input.substr(colon_pos + 1, std::string::npos);
		input = input.substr(0, colon_pos);
		has_last_param = true;
	}

	std::stringstream ss(input);
	std::string param;

	while (getline(ss, param,  ' '))
		if (!param.empty())
			vec.push_back(param);
	if (has_last_param)
		vec.push_back(last_param);
}

void	HandlerReceive::execCmds(void)
{
	for (size_t i = 0; i < _full_cmds.size(); i++)
	{
		std::vector<std::string> params;
		parseCmdParam(_full_cmds[i], params);
		if (params.empty())
			continue ;
		std::string cmd_name = params.at(0);
		params.erase(params.begin());

		Command* cmd = NULL;
		if (cmd_name == "NICK")
			cmd = new Nick(_server, _client, cmd_name, params);
		else if (cmd_name == "PASS")
			cmd = new Pass(_server, _client, cmd_name, params);
		else if (cmd_name == "QUIT")
			cmd = new Quit(_server, _client, cmd_name, params);
		else if (cmd_name == "USER")
			cmd = new User(_server, _client, cmd_name, params);
		else if (cmd_name == "PRIVMSG")
			cmd = new PrivMsg(_server, _client, cmd_name, params);
		else if (cmd_name == "JOIN")
			cmd = new Join(_server, _client, cmd_name, params);
		else if (cmd_name == "MODE")
			cmd = new Mode(_server, _client, cmd_name, params);
		else if (cmd_name == "TOPIC")
			cmd = new Topic(_server, _client, cmd_name, params);
		else if (cmd_name == "INVITE")
			cmd = new Invite(_server, _client, cmd_name, params);
		else if (cmd_name == "KICK")
			cmd = new Kick(_server, _client, cmd_name, params);
		else if (cmd_name == "PART")
			cmd = new Part(_server, _client, cmd_name, params);
		else
			cmd = new UnknownCommand(_server, _client, cmd_name, params);
		_cmds.push_back(cmd);
	}

	for (size_t i = 0; i < _cmds.size(); i++)
		_cmds.at(i)->enactCommand();
}

HandlerReceive::HandlerReceive(Client& client, Server& server) : _client(client), _server(server)
{}

HandlerReceive::~HandlerReceive(void)
{
	for (size_t i = 0; i < _cmds.size(); i++)
		delete _cmds.at(i);
}
