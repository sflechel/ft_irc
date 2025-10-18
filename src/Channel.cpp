#include "Channel.hpp"
#include "Client.hpp"

Channel::Channel(Client& user) : _user_limit(-1), _is_invite_only(0), _is_topic_restricted(0)
{
    _users.push_back(&user);
    _operators.push_back(&user);
	(void)_user_limit;
	(void)_is_invite_only;
	(void)_is_topic_restricted;
}

Channel::~Channel(void)
{}
