#include "commands/Topic.hpp"
#include "Channel.hpp"
#include "Command.hpp"
#include <string>
#include <vector>
#include <iostream>

Topic::Topic(Server& server, Client& user, std::string cmd_name, std::vector<std::string> params) : Command(server, user, cmd_name, params)
{}

void	Topic::enactCommand(void)
{
	int size = _params.size();
	if (size < 1 || size > 2)
		_user.addResponse(_respbldr.buildResponseNum(_cmd_name, ERR_NEEDMOREPARAMS));
	else if (!_user.getIsRegistered())
		_user.addResponse(_respbldr.buildResponseNum("", ERR_NOTREGISTERED));
	else
	{
		Channel*	channel = _server.getChannel(_params.at(0));
		if (channel == NULL)
			_user.addResponse(_respbldr.buildResponseNum(channel->getName(), ERR_NOSUCHCHANNEL));
		else if (size == 1)
		{
			if (channel->getTopic().empty())
				_user.addResponse(_respbldr.buildResponseNum(channel->getName(), RPL_NOTOPIC));
			else
				_user.addResponse(_respbldr.buildResponseNum(channel->getName() + " :" + channel->getTopic(), RPL_TOPIC));
		}
		else
		{
			std::cout << channel->getIsTopicRestricted() << "\n";
			if (channel->getIsTopicRestricted() && !channel->isUserOp(_user.getNickname()))
				_user.addResponse(_respbldr.buildResponseNum(channel->getName(), ERR_CHANOPRIVSNEEDED));
			else
			{
				channel->setTopic(_params.at(1));
				std::string msg = _respbldr.buildResponseNum(channel->getName() + " :" + channel->getTopic(), RPL_TOPIC);
				_user.addResponse(msg);
				channel->sendChannelMessage(msg, _user);
			}
		}
	}
}

Topic::~Topic(void)
{}
