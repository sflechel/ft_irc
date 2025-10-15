#include "Client.hpp"
#include <string>

int	Client::get_my_fd(void) const
{
	return (this->_my_fd);
}

std::string Client::getResponse(void) const
{
    return (this->_response);
}

std::string Client::getNickname(void) const
{
    return (this->_nickname);
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

//COMMANDS
void    Client::Pass(Command& command, std::string& password)
{

}
