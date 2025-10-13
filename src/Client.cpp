#include "Client.hpp"
#include <string>

int	Client::get_my_fd(void)
{
	return (this->_my_fd);
}

std::string Client::getResponse(void)
{
    return (this->_response);
}

void    Client::setResponse(std::string response)
{
    this->_response = response;
}

Client::Client(int fd) : _my_fd(fd)
{
	_nickname = std::string();
	_username = std::string();
	_is_registered = false;
}

Client::~Client(void) {}
