#include "commands/Kick.hpp"
#include "Channel.hpp"
#include "Command.hpp"
#include <string>
#include <vector>

Kick::Kick(Server& server, Client& user, std::string cmd_name, std::vector<std::string> params) : Command(server, user, cmd_name, params)
{}

void	Kick::kick(Channel& channel, std::string to_kick)
{
	std::string		channel_name = channel.getName();
	std::string		msg = _respbldr.buildResponse("KICK", channel_name + " " + to_kick);

	_user.setResponse(msg);
	channel.sendChannelMessage(msg, _user);
	channel.leave(to_kick);
}

void	Kick::enactCommand(void)
{
	int size = _params.size();

	if (size != 2)
	{
		_user.setResponse(_respbldr.buildResponseNum(_cmd_name, ERR_NEEDMOREPARAMS));
		return;
	}
	else if (!_user.getIsRegistered())
	{
		_user.setResponse(_respbldr.buildResponseNum("", ERR_NOTREGISTERED));
		return;
	}
	Channel*	channel = _server.getChannel(_params.at(0));
	std::string	channel_name = _params.at(0);
	std::string	is_kicked = _params.at(1);
	std::string	kicking = _user.getNickname();

	if (channel == NULL)
		_user.setResponse(_respbldr.buildResponseNum(channel_name, ERR_NOSUCHCHANNEL));
	else if (!channel->isUserInChannel(kicking))
		_user.setResponse(_respbldr.buildResponseNum(channel_name, ERR_NOTONCHANNEL));
	else if (!channel->isUserInChannel(is_kicked))
		_user.setResponse(_respbldr.buildResponseNum(is_kicked + " " + channel_name, ERR_USERNOTINCHANNEL));
	else if (!channel->isUserOp(kicking))
		_user.setResponse(_respbldr.buildResponseNum(channel_name, ERR_CHANOPRIVSNEEDED));
	else
		this->kick(*channel, is_kicked);
}

Kick::~Kick(void)
{}
