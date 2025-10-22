#include "HandlerRespond.hpp"
#include "Server.hpp"
#include <string>
#include <sys/epoll.h>
#include <stdexcept>

HandlerRespond::HandlerRespond(Client& client, Server& server) : _client(client), _server(server)
{}

void	HandlerRespond::removeClientFromSenders(void)
{
	Client*	client = &_client;
	struct epoll_event  poll_opts;

	_server.removeSender(client);
	poll_opts.events = EPOLLIN;
	int conn_fd = client->getFd();
	poll_opts.data.fd = conn_fd;
	poll_opts.data.ptr = client;
	if (epoll_ctl(_server.getEpollFd(), EPOLL_CTL_MOD, conn_fd, &poll_opts) == -1)
		throw std::runtime_error("failed to change client fd to only listening in");
}

void	HandlerRespond::respond(void)
{
	int byte_sent;
	std::string response = this->_client.getResponse();
	if (response.empty())
		return ;
	byte_sent = send(this->_client.getFd(), response.c_str(), response.size(), 0);
	response.erase(0, byte_sent);
	this->_client.setResponse(response);

	if (response.empty())
		removeClientFromSenders();
}

HandlerRespond::~HandlerRespond()
{}
