#include "Command.hpp"
#include <cstddef>
#include <string>
#include <vector>
#include <iostream>

Command::Command(Server& server, Client& user, std::string cmd_name, std::vector<std::string> params) :
	_server(server),
	_user(user),
	_cmd_name(cmd_name),
	_params(params),
	_respbldr(_server.getName(), _user)
{

	std::cout << "cmd: " << cmd_name << "\nparam: ";
	for (size_t i = 0; i < params.size(); i++)
	{
		std::cout << params[i];
		if (i != params.size() - 1)
			std::cout << "|";
	}
	std::cout << "\n";
}

Command::~Command()
{}
