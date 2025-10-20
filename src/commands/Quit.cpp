#include "commands/Quit.hpp"
#include "Command.hpp"
#include <cstddef>
#include <iterator>
#include <string>
#include <vector>

Quit::Quit(Server& server, Client& user, std::string cmd_name, std::vector<std::string> params) : Command(server, user, cmd_name, params)
{}

void	Quit::enactCommand(void)
{
	std::string message = ":" + _server.getName() + " ERROR\r\n";

	_user.setResponse(message);

	if (_user.getNickname().empty())
	{
		std::ptrdiff_t  index = std::distance(*_server.getNewClients().data(), &_user);
		_server.removeNewClient(index);
	}
	else
	{
		std::map<std::string, Channel*>  channels = _server.getChannels();
		std::map<std::string, Channel*>::iterator   it;
		for (it = channels.begin() ; it != channels.end() ; it++)
			it->second->leave(_user.getNickname());
		_server.removeClient(_user.getNickname());
	}
}

Quit::~Quit(void)
{}
