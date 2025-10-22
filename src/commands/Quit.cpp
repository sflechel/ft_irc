#include "commands/Quit.hpp"
#include "Command.hpp"
#include <string>
#include <vector>

Quit::Quit(Server& server, Client& user, std::string cmd_name, std::vector<std::string> params) : Command(server, user, cmd_name, params)
{}

void	Quit::enactCommand(void)
{
	std::string message = ":" + _server.getName() + " ERROR\r\n";

	_user.addResponse(message);

	if (_user.getNickname().empty())
	{
		_server.removeNewClient(&_user);
	}
	else
		_server.removeClient(_user.getNickname());
}

Quit::~Quit(void)
{}
