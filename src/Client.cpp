#include "Client.hpp"
#include <string>

bool	Client::getIsRegistered(void) const
{
	return (this->_is_registered);
}
void	Client::setIsRegistered(bool state)
{
    _is_registered = state;
}


int	Client::getMyFd(void) const
{
	return (this->_my_fd);
}

std::string Client::getResponse(void) const
{
    return (this->_response);
}

std::string Client::getDataReceived(void) const
{
    return (this->_data_received);
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

void    Client::setDataReceived(std::string data)
{
    this->_data_received = data;
}

Client::Client(int fd) : _my_fd(fd)
{
	_nickname = std::string();
	_username = std::string();
	_is_registered = false;
}

Client::~Client(void) {}
