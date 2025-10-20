#include "Channel.hpp"
#include "Client.hpp"
#include "Server.hpp"
#include <set>
#include <string>

Channel::Channel(Server& server, std::string name, Client& user) : _name(name), _server(server), _user_limit(-1), _is_invite_only(0), _is_topic_restricted(0)
{
    _users.insert(user.getNickname());
    _operators.insert(user.getNickname());
    (void)_user_limit;
    (void)_is_invite_only;
    (void)_is_topic_restricted;
}

void    Channel::addUser(std::string nickname)
{
    _users.insert(nickname);
}

void    Channel::leave(std::string nickname)
{
    _users.erase(nickname);
    _operators.erase(nickname);
}

void	Channel::sendChannelMessage(const std::string& message, const Client& sender) const
{
	std::set<std::string>::iterator	it;
	for (it = _users.begin() ; it != _users.end() ; it++)
	{
		Client* target = _server.getClient(*it);
		if (target != NULL && target != &sender)
			target->setResponse(message);
	}
}

bool Channel::isUserOperator(const std::string &username) const
{
	std::set<std::string>::iterator	it;
	for (it = _operators.begin() ; it != _operators.end() ; it++)
		if (username.compare(*it) == 0)
			return (true);
	return (false);
}

bool    Channel::getIsInviteOnly(void) const
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

bool    Channel::getIsTopicRestricted(void)
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

bool    Channel::getIsUser(std::string nickname)
{
    if (_users.find(nickname) == _users.end())
        return false;
    return true;
}

bool    Channel::getIsOp(std::string nickname)
{
    if (_operators.find(nickname) == _operators.end())
        return false;
    return true;
}

std::string    Channel::getTopic(void) const
{
    return _topic;
}

void    Channel::setTopic(std::string topic)
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
