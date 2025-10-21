#include "HandlerRespond.hpp"
#include <cerrno>
#include <string>
#include <sys/socket.h>

HandlerRespond::HandlerRespond(Client& client) : _client(client)
{}

void	HandlerRespond::respond(void)
{
	int byte_sent;
	std::string response = this->_client.getResponse();
	if (response.empty())
		return ;
	byte_sent = send(this->_client.getFd(), response.c_str(), response.size(), 0);
	response.erase(0, byte_sent);
	this->_client.setResponse(response);
}

HandlerRespond::~HandlerRespond()
{}
