#include "Client.hpp"
#include <string>

bool	Client::getSentPassword(void) const
{
	return (this->_sent_password);
}
void	Client::setSentPassword(bool state)
{
    _sent_password = state;
}

bool	Client::getIsRegistered(void) const
{
	return (this->_is_registered);
}
void	Client::setIsRegistered(bool state)
{
    _is_registered = state;
}

int	Client::getFd(void) const
{
	return (this->_fd);
}

std::string Client::getResponse(void) const
{
    return (this->_response);
}

std::string Client::getRequest(void) const
{
    return (this->_request);
}

void    Client::setRealname(std::string realname)
{
    _realname =  realname;
}

std::string Client::getRealname(void) const
{
    return (this->_realname);
}

void    Client::setNickname(std::string nickname)
{
    _nickname =  nickname;
}

std::string Client::getNickname(void) const
{
    return (this->_nickname);
}

void    Client::setUsername(std::string username)
{
    _username = username;
}

std::string Client::getUsername(void) const
{
    return (this->_username);
}

void    Client::setResponse(std::string response)
{
    this->_response = response;
}

void    Client::setRequest(std::string request)
{
    this->_request = request;
}

Client::Client(int fd) : _fd(fd)
{
	_nickname = std::string();
	_username = std::string();
	_is_registered = false;
	_sent_password = false;
}

Client::~Client(void) {}
