#include "Channel.hpp"
#include "Client.hpp"
#include <string>

Channel::Channel(std::string name, Client& user) : _name(name), _user_limit(-1), _is_invite_only(0), _is_topic_restricted(0)
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

std::string Channel::getKey(void)
{
    return _key;
}

Channel::~Channel(void)
{}
