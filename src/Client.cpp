#include "Client.hpp"

int	Client::get_my_fd()
{
	return (_my_fd);
}

Client::Client(int fd) : _my_fd(fd)
{
	_nickname = std::string();
	_username = std::string();
	_is_registered = false;
}

Client::~Client() {}
