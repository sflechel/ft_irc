#include "Server.hpp"
#include <csignal>

Server::Server(std::string password) : _password(password), _name("cIRCussy")
{}

Server::~Server()
{
	for (std::set<Client*>::iterator it = _new_clients.begin() ; it != _new_clients.end() ; it++)
		delete *it;
	for (std::map<std::string, Client*>::iterator it = _clients.begin(); it != _clients.end(); it++)
		delete it->second;
	for (std::map<std::string, Channel*>::iterator it = _channels.begin(); it != _channels.end(); it++)
		delete it->second;
	close(_master_socket);
	close(_epollfd);
}
