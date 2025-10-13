#include "HandlerConnection.hpp"
#include <fcntl.h>
#include <iostream>
#include <stdexcept>
#include <sys/socket.h>
#include <sys/epoll.h>

HandlerConnection::HandlerConnection(int master_sock) : _master_sock(master_sock)
{
}

Client	HandlerConnection::accept_connection()
{
	struct sockaddr	addr;
	socklen_t		len_addr;
	int				conn_fd;

	conn_fd = accept(_master_sock, &addr, &len_addr);
	if (conn_fd == -1)
		throw std::runtime_error("failed to accept connection");

	if (fcntl(conn_fd, F_SETFL, O_NONBLOCK) == -1)
		throw std::runtime_error("failed to set connection socket to non blocking");

	std::cout << "Server connected to a client!" << std::endl;

	return (Client(conn_fd));
}

HandlerConnection::~HandlerConnection()
{}
