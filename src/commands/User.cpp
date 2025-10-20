#include "commands/User.hpp"
#include "Command.hpp"
#include "ResponseBuilder.hpp"
#include <string>
#include <vector>

User::User(Server& server, Client& user, std::string cmd_name, std::vector<std::string> params) : Command(server, user, cmd_name, params)
{}

void	User::enactCommand(void)
{
	ResponseBuilder respbldr = ResponseBuilder(_server.getName(), _user);

	if (!_user.getSentPassword())
		_user.setResponse(respbldr.buildResponseNum("", ERR_PASSWDMISMATCH));
	else if (_params.size() != 4)
		_user.setResponse(respbldr.buildResponseNum(_cmd_name, ERR_NEEDMOREPARAMS));
	else if (_user.getIsRegistered())
		_user.setResponse(respbldr.buildResponseNum("", ERR_ALREADYREGISTERED));
	else
	{
		_user.setUsername(_params.at(0));
		_user.setRealname(_params.at(3));

		if (!_user.getNickname().empty())
		{
			_user.setResponse(respbldr.buildResponseNum("", RPL_WELCOME));
			_user.setIsRegistered(true);
		}
	}
}

User::~User(void)
{}
