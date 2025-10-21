#include "Channel.hpp"
#include "Client.hpp"
#include "ResponseBuilder.hpp"
#include "Server.hpp"
#include <set>
#include <string>

Channel::Channel(Server& server, std::string name, Client& user) : _name(name), _server(server), _user_limit(-1), _is_invite_only(0), _is_topic_restricted(0)
{
	std::string nickname = user.getNickname();
	_users.insert(nickname);
	_operators.insert(nickname);
}

void	Channel::addUser(std::string nickname)
{
	_invited.erase(nickname);
	_users.insert(nickname);
}

void	Channel::leave(std::string nickname)
{
	_users.erase(nickname);
	_operators.erase(nickname);
	_invited.erase(nickname);
}

void	Channel::sendChannelMessage(const std::string& message, const Client& sender) const
{
	std::set<std::string>::iterator	it;
	for (it = _users.begin() ; it != _users.end() ; it++)
	{
		Client* target = _server.getClient(*it);
		if (target != NULL && target != &sender)
			target->addResponse(message);
	}
}

void	Channel::removeOp(const std::string& nickname)
{
	_operators.erase(nickname);
}

void	Channel::addOp(const std::string& nickname)
{
	_operators.insert(nickname);
}

void	Channel::addInvited(const std::string& nickname)
{
	_invited.insert(nickname);
}

bool	Channel::getIsInviteOnly(void) const
{
	return _is_invite_only;
}

void	Channel::setUserLimit(const int limit)
{
	_user_limit = limit;
}

void	Channel::setKey(const std::string& str)
{
	_key = str;
}

void	Channel::setIsInviteOnly(const bool flag)
{
	_is_invite_only = flag;
}

void	Channel::setIsTopicRestricted(const bool flag)
{
	_is_topic_restricted = flag;
}

bool	Channel::getIsTopicRestricted(void)
{
	return _is_topic_restricted;
}

int Channel::getUserLimit(void) const
{
	return _user_limit;
}

std::set<std::string>&  Channel::getUsers(void)
{
	return _users;
}

bool	Channel::isUserInChannel(std::string nickname)
{
	if (_users.find(nickname) == _users.end())
		return false;
	return true;
}

bool	Channel::isUserOp(std::string nickname)
{
	if (_operators.find(nickname) == _operators.end())
		return false;
	return true;
}

bool	Channel::isUserInvited(std::string nickname)
{
	if (_invited.find(nickname) == _invited.end())
		return false;
	return true;
}

std::string	Channel::getTopic(void) const
{
	return _topic;
}

void	Channel::setTopic(std::string topic)
{
	_topic = topic;
}

std::string Channel::getKey(void) const
{
	return _key;
}

std::string Channel::getName(void) const
{
	return _name;
}

Channel::~Channel(void)
{}
