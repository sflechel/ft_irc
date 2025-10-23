#include "PrivMsg.hpp"
#include <string>
#include <sys/socket.h>
#include <iostream>

PrivMsg::PrivMsg(std::string nickname, std::string sender, std::string cmd_name, std::vector<std::string> params) : Command(nickname, sender, cmd_name, params)
{}

void	PrivMsg::enactCommand(int socket)
{
	std::string	target;
	if (_params.at(0).at(0) == '#')
		target = _params.at(0);
	else
		target = _sender;

	std::string command = _params.at(1);
	std::string	base_response = ":" + _nickname + " PRIVMSG " + target + " ";
	std::string response;

	if (command.size() >= 4 && command.compare(command.size()-4, 4, "quoi") == 0)
		response += base_response + ":feur!\r\n";

	if (command.compare(0, 14, "/shifumi rock") == 0)
		response += base_response + ":paper. I win. You lose! Loser!\r\n";
	else if (command.compare(0, 15, "/shifumi paper") == 0)
		response += base_response + ":scissors. I win. You lose! Loser!\r\n";
	else if (command.compare(0, 18, "/shifumi scissors") == 0)
		response += base_response + ":rock. I win. You lose! Loser!\r\n";
	else if (command.compare(0, 8, "/shifumi") == 0)
		response += base_response + ":bad input. You lose. I win! Loser!\r\n";

	if (!response.empty())
		send(socket, response.c_str(), response.size(), 0);
}

PrivMsg::~PrivMsg(void)
{}

