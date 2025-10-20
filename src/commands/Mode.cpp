#include "commands/Mode.hpp"
#include "Channel.hpp"
#include "Client.hpp"
#include "ResponseBuilder.hpp"
#include "Server.hpp"
#include <sstream>

Mode::Mode(Server& server, Client& user, std::string cmd_name, std::vector<std::string> params) : Command(server, user, cmd_name, params)
{}

void	Mode::enactCommand(void)
{
	ResponseBuilder respbldr = ResponseBuilder(_server.getName(), _user);
	if (!_user.getIsRegistered())
		_user.setResponse(respbldr.buildResponseNum("", ERR_NOTREGISTERED));
	else if (_params.size() < 2 || _params.size() > 3 || (_params.size() == 3 && _params.at(1).empty()))
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
			if (mode.length() != 2 || mode[0] != '-' || mode[0] != '+')
				_user.setResponse(":" + _server.getName() + " 472 " + _user.getNickname() + " " + mode + " :is invalid/unknown mode char to me for " + target + "\r\n" );
			else if (mode[1] == 'i')
				channel->setIsInviteOnly(mode[0] == '+');
			else if (mode[1] == 't')
				channel->setIsTopicRestricted(mode[0] == '+');
			else if (mode[1] == 'k')
			{
				if (mode[0] == '-')
					channel->setKey("");
				else if (_params.size() == 3)
					channel->setKey(_params.at(1));
			}
			else if (mode[1] == 'o')
			{
				//Client *client;
				if (mode[0] == '-')
				{
				}
			}
			else if (mode[1] == 'l')
			{
				if (mode[0] == '-')
					channel->setUserLimit(-1);
				else if (_params.size() == 3)
				{
					std::istringstream ss(_params.at(1));
					int limit = -1;
					ss >> limit;
					if (limit > 0)
						channel->setUserLimit(limit);
				}
			}
		}
	}
}

Mode::~Mode(void)
{}

