#include "Server.hpp"


std::string Server::getPassword(void) const
{
	return (this->_password);
}

std::string Server::getName(void) const
{
	return (this->_name);
}

Client* Server::getClient(std::string nickname)
{
	std::map<std::string, Client*>::iterator it = _clients.find(nickname);
	if (it == _clients.end())
		return (NULL);
	return (it->second);
}

std::map<std::string, Channel*>&	Server::getChannels(void)
{
	return _channels;
}

Channel*	Server::getChannel(std::string name)
{
	std::map<std::string, Channel*>::iterator it = _channels.find(name);
	if (it == _channels.end())
		return (NULL);
	return (it->second);
}

std::set<Client*>&	Server::getNewClients(void)
{
	return (_new_clients);
}

int	Server::getMasterSocket(void) const
{
	return _master_socket;
}

int	Server::getEpollFd(void) const
{
	return _epollfd;
}
