#include "commands/Invite.hpp"
#include "Channel.hpp"
#include "Command.hpp"
#include "ResponseBuilder.hpp"
#include <string>
#include <vector>

Invite::Invite(Server& server, Client& user, std::string cmd_name, std::vector<std::string> params) : Command(server, user, cmd_name, params)
{

}

void	Invite::invite(Channel* channel, std::string to_invite)
{
	std::string channel_name = channel->getName();
	std::string sender = _user.getNickname();

	channel->addUser(to_invite);
	_server.getClient(to_invite)->addResponse(":" + sender + " INVITE " + to_invite + " " + channel_name + "\r\n");
	_user.addResponse(_respbldr.buildResponseNum(channel_name + " " + to_invite, RPL_INVITING));
}

void	Invite::enactCommand(void)
{
	if (_params.size() != 2)
	{
		_user.addResponse(_respbldr.buildResponseNum(_cmd_name, ERR_NEEDMOREPARAMS));
		return;
	}
	else if (!_user.getIsRegistered())
	{
		_user.addResponse(_respbldr.buildResponseNum("", ERR_NOTREGISTERED));
		return;
	}
	std::string channel_name = _params.at(1);
	Channel*	channel = _server.getChannel(channel_name);
	std::string to_invite = _params.at(0);
	std::string sender = _user.getNickname();
	if (channel == NULL)
		_user.addResponse(_respbldr.buildResponseNum(_params.at(1), ERR_NOSUCHCHANNEL));
	else if (!_server.getClient(to_invite))
		_user.addResponse(_respbldr.buildResponseNum(to_invite, ERR_NOSUCHNICK));
	else if (!channel->isUserInChannel(sender))
		_user.addResponse(_respbldr.buildResponseNum(channel_name, ERR_NOTONCHANNEL));
	else if (channel->isUserInChannel(to_invite))
		_user.addResponse(_respbldr.buildResponseNum(to_invite + " " + channel_name, ERR_USERONCHANNEL));
	else if (channel->getIsInviteOnly() && !channel->isUserOp(sender))
		_user.addResponse(_respbldr.buildResponseNum(channel_name, ERR_CHANOPRIVSNEEDED));
	else
		this->invite(channel, to_invite);
}

Invite::~Invite(void)
{}
