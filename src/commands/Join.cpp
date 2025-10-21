#include "commands/Join.hpp"
#include "Channel.hpp"
#include "Client.hpp"
#include "Command.hpp"
#include "ResponseBuilder.hpp"
#include "Server.hpp"
#include <cstddef>
#include <map>
#include <string>
#include <vector>
#include <iostream>

Join::Join(Server& server, Client& user, std::string cmd_name, std::vector<std::string> params) : Command(server, user, cmd_name, params)
{}

Join::~Join(void)
{}

void	Join::joinMessage(Channel& channel)
{
	std::string		name = channel.getName();
	std::string		msg = _respbldr.buildResponse("JOIN", name);

	_user.addResponse(msg);
	channel.sendChannelMessage(msg, _user);
	if (!channel.getTopic().empty())
		_user.addResponse(_respbldr.buildResponseNum(name + " :" + channel.getTopic(), RPL_TOPIC));
	else
		_user.addResponse(_respbldr.buildResponseNum(name, RPL_NOTOPIC));
	_user.addResponse(_respbldr.buildNamReply(channel));
	_user.addResponse(_respbldr.buildResponseNum(name, RPL_ENDOFNAMES));
}

void	Join::joinChannel(Channel& channel)
{
	channel.addUser(_user.getNickname());
	this->joinMessage(channel);
}

void	Join::joinChannel(Channel& channel, std::string name, std::string key)
{
	if (key == channel.getKey())
	{
		channel.addUser(_user.getNickname());
		this->joinMessage(channel);
	}
	else
		_user.addResponse(_respbldr.buildResponseNum(name, ERR_BADCHANNELKEY));
}

void	Join::leaveAllChannels(void)
{
	std::map<std::string, Channel*>  channels = _server.getChannels();
	std::map<std::string, Channel*>::iterator   it;

	for (it = channels.begin() ; it != channels.end() ; it++)
	{
		std::string		name = it->second->getName();
		std::string		msg = ":" + _user.getNickname() + " PART " + name + "\r\n";
		_user.addResponse(msg);
		it->second->sendChannelMessage(msg, _user);
		it->second->leave(_user.getNickname());
	}
}

void	Join::createChannel(std::string name)
{
	_server.createChannel(name, _user);
	this->joinMessage(*_server.getChannel(name));
}

void	Join::enactCommand(void)
{
	int size = _params.size();

	if (!_user.getIsRegistered())
		_user.addResponse(_respbldr.buildResponseNum("", ERR_NOTREGISTERED));
	else if ((size < 1 || size > 2) || _params.at(0).empty())
		_user.addResponse(_respbldr.buildResponseNum(_cmd_name, ERR_NEEDMOREPARAMS));
	else if (size == 1 && _params.at(0) == "0")
		this->leaveAllChannels();
	else
	{
		std::string	name = _params.at(0);
		if (name.size() < 2 || name.at(0) != '#')
			_user.addResponse(_respbldr.buildResponseNum(name, ERR_NOSUCHCHANNEL));
		else
		{
			Channel*	channel = _server.getChannel(name);
			if (channel == NULL)
				this->createChannel(name);
			else if (channel->getIsInviteOnly())
				_user.addResponse(_respbldr.buildResponseNum(name, ERR_INVITEONLYCHAN));
			else if (channel->getUserLimit() != -1 && (long)channel->getUsers().size() >= channel->getUserLimit())
				_user.addResponse(_respbldr.buildResponseNum(name, ERR_CHANNELISFULL));
			else
			{
				std::cout << "testtsetst\n";
				if (size == 1)
					this->joinChannel(*channel);
				else
					this->joinChannel(*channel, name, _params.at(1));
			}
		}
	}
}
