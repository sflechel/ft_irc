#include "Invite.hpp"
#include <string>
#include <sys/socket.h>

Invite::Invite(std::string nickname, std::string sender, std::string cmd_name, std::vector<std::string> params) : Command(nickname, sender, cmd_name, params)
{}

void	Invite::enactCommand(int socket)
{
	std::string channel_name = _params.at(1);
	std::string	response = ":" + _nickname + " JOIN " + channel_name + "\r\n";
	send(socket, response.c_str(), response.size(), 0);
}

Invite::~Invite(void)
{}
