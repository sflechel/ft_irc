#include "commands/Part.hpp"
#include "Channel.hpp"
#include "Command.hpp"
#include "ResponseBuilder.hpp"
#include <cstddef>
#include <string>
#include <vector>

Part::Part(Server& server, Client& user, std::string cmd_name, std::vector<std::string> params) : Command(server, user, cmd_name, params)
{}

void	Part::part(Channel& channel)
{
	std::string		msg = ":" + _user.getNickname() + " PART " + channel.getName() + "\r\n";
	_user.addResponse(msg);
	channel.sendChannelMessage(msg, _user);
	channel.leave(_user.getNickname());
}

void	Part::enactCommand(void)
{
	int size = _params.size();

	if (!_user.getIsRegistered())
		_user.addResponse(_respbldr.buildResponseNum("", ERR_NOTREGISTERED));
	else if (size != 1)
		_user.addResponse(_respbldr.buildResponseNum(_cmd_name, ERR_NEEDMOREPARAMS));
	else
	{
		Channel*	channel = _server.getChannel(_params.at(0));
		if (channel == NULL)
			_user.addResponse(_respbldr.buildResponseNum(_params.at(0), ERR_NOSUCHCHANNEL));
		else if (!channel->isUserInChannel(_user.getNickname()))
			_user.addResponse(_respbldr.buildResponseNum(_params.at(0), ERR_NOTONCHANNEL));
		else
			this->part(*channel);
	}
}

Part::~Part(void)
{}
