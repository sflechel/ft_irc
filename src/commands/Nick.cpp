#include "commands/Nick.hpp"
#include "Command.hpp"
#include <cstddef>
#include <string>
#include <vector>

Nick::Nick(Server& server, Client& user, std::string cmd_name, std::vector<std::string> params) : Command(server, user, cmd_name, params)
{}

void	Nick::enactCommand(void)
{
	if (!_user.getSentPassword())
		_user.addResponse(_respbldr.buildResponseNum(_cmd_name, ERR_NOPASSWD));
	else if (_params.size() != 1 || _params.at(0).empty())
		_user.addResponse(_respbldr.buildResponseNum(_cmd_name, ERR_NONICKNAMEGIVEN));
	else if (_server.getClient(_params.at(0)) != NULL)
		_user.addResponse(_respbldr.buildResponseNum(_params.at(0), ERR_NICKNAMEINUSE));
	else if (_user.getNickname().empty())
	{
		_server.registerClient(&_user, _params.at(0));

		if (!_user.getUsername().empty())
		{
			_user.addResponse(_respbldr.buildResponseNum("", RPL_WELCOME));
			_user.setIsRegistered(true);
		}
	}
	else
		_server.updateNickname(&_user, _params.at(0));//TODO when updating nick, update also channels
}

Nick::~Nick(void)
{}
