#include "HandlerConnection.hpp"
#include "Client.hpp"
#include <fcntl.h>
#include <iostream>
#include <stdexcept>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <vector>

HandlerConnection::HandlerConnection(int masterSock) : _masterSock(masterSock)
{
}

Client*	HandlerConnection::acceptConnection()
{
	struct sockaddr	addr;
	socklen_t		len_addr = 0;
	int				conn_fd;

	conn_fd = accept(this->_masterSock, &addr, &len_addr);
	if (conn_fd == -1)
		throw std::runtime_error("failed to accept connection");

	if (fcntl(conn_fd, F_SETFL, O_NONBLOCK) == -1)
		throw std::runtime_error("failed to set connection socket to non blocking");

	std::cout << "Server connected to a client!" << std::endl;

    Client* output = new Client(conn_fd);
	return (output);
}

void    HandlerConnection::registerClient(Client* newClient, std::vector<Client*>& listClients, int epollfd)
{
    struct epoll_event  poll_opts;

    listClients.push_back(newClient);
    poll_opts.events = EPOLLIN | EPOLLOUT;
    int conn_fd = newClient->getFd();
    poll_opts.data.fd = conn_fd;
    poll_opts.data.ptr = newClient;
    if (epoll_ctl(epollfd, EPOLL_CTL_ADD, conn_fd, &poll_opts) == -1)
        throw std::runtime_error("failed to add connection to epoll");
}

HandlerConnection::~HandlerConnection()
{}
