#include "Server.hpp"
#include <iostream>

void	Server::forceQuitClient(Client* client)
{
	if (client == NULL)
		return;
	std::string	nickname = client->getNickname();
	if (nickname.empty())
		removeNewClient(client);
	else
		removeClient(nickname);
}

void	Server::removeNewClient(Client* client)
{
	std::set<Client*>::iterator   it = _new_clients.find(client);

	if (it == _new_clients.end())
		return;
	delete *it;
	_new_clients.erase(it);
	std::cout << "Client quit\n";

	it = _senders.find(client);
	if (it == _senders.end())
		return;
	_senders.erase(it);
}

void	Server::removeClient(std::string nickname)
{
	std::map<std::string, Channel*>  channels = this->getChannels();
	std::map<std::string, Channel*>::iterator   it;
	Client*	client = this->getClient(nickname);
	for (it = channels.begin() ; it != channels.end() ; it++)
	{
		if (it->second->isUserInChannel(nickname))
		{
			std::string		name = it->second->getName();
			std::string		msg = ":" + nickname + " PART " + name + "\r\n";
			client->addResponse(msg);
			it->second->sendChannelMessage(msg, *client);
		}
		it->second->leave(client->getNickname());
	}
	delete _clients.at(nickname);
	_clients.erase(nickname);
	std::cout << "Client quit\n";


	std::set<Client*>::iterator	iter = _senders.find(client);
	if (iter == _senders.end())
		return;
	_senders.erase(iter);
}

void	Server::registerClient(Client* client, std::string nickname)
{
	std::pair<std::string, Client*> pair(nickname, client);
	client->setNickname(nickname);
	std::set<Client*>::iterator it = _new_clients.find(client);
	if (it == _new_clients.end())
		return;
	_new_clients.erase(it);
	_clients.insert(pair);
}

void	Server::createChannel(std::string name, Client& user)
{
	Channel *new_channel = new Channel(*this, name, user);
	std::pair<std::string, Channel*>	pair(name, new_channel);
	_channels.insert(pair);
}

void	Server::updateNickname(Client* client, std::string new_nickname)
{
	std::string	old_nickname = client->getNickname();
	std::map<std::string, Channel*>::iterator   it;
	for (it = _channels.begin() ; it != _channels.end() ; it++)
	{
		if (it->second->isUserInChannel(old_nickname))
		{
			std::string		name = it->second->getName();
			std::string		msg = ":" + old_nickname + " NICK " + new_nickname + "\r\n";
			client->addResponse(msg);
			it->second->sendChannelMessage(msg, *client);
			it->second->updateNickname(old_nickname, new_nickname);
		}
		if (it->second->isUserInvited(old_nickname))
			it->second->updateNicknameInvited(old_nickname, new_nickname);
		it->second->leave(client->getNickname());
	}

	_clients.erase(client->getNickname());
	client->setNickname(new_nickname);
	std::pair<std::string, Client*> pair(new_nickname, client);
	_clients.insert(pair);

}

