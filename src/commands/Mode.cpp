#include "commands/Mode.hpp"
#include "Channel.hpp"
#include "ResponseBuilder.hpp"
#include "Server.hpp"

Mode::Mode(Server& server, Client& user, std::string cmd_name, std::vector<std::string> params) : Command(server, user, cmd_name, params)
{}

void    Mode::enactCommand(void)
{
    ResponseBuilder respbldr = ResponseBuilder(_server.getName(), _user);
	if (!_user.getIsRegistered())
		_user.setResponse(respbldr.buildResponseNum("", ERR_NOTREGISTERED));
	else if (_params.size() < 2 || _params.size() > 3)
        _user.setResponse(respbldr.buildResponseNum(_cmd_name, ERR_NEEDMOREPARAMS));
	else
	{
		std::string& target = _params.at(0);
		Channel* channel = _server.getChannel(target);
		if (channel == NULL)
			_user.setResponse(respbldr.buildResponseNum(target, ERR_NOSUCHCHANNEL));
		else if (!channel->isUserOperator(_user.getNickname()))
			_user.setResponse(respbldr.buildResponseNum(target, ERR_NOPRIVILEGES));//TODO a tester
		else
		{
			const std::string mode = _params.at(1);
			if (mode.length() != 2 || mode[0] != '-' || mode[0] != '+')//is a know mode
				_user.setResponse(":" + _server.getName() + " 472 " + _user.getNickname() + " " + mode + " :is unknown mode char to me for " + target + "\r\n" );
			else
			{}
		}
	}
}

Mode::~Mode(void)
{}

