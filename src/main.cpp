#include "Server.hpp"
#include <csignal>
#include <cstdlib>
#include <exception>
#include <stdexcept>
#include <iostream>
#include <signal.h>
#include <string>

volatile sig_atomic_t	g_signum = 0;

void	signalHandler(int signum)
{
	if (signum == SIGINT)
		g_signum = SIGINT;
}

void	setSignalHandler(void)
{
	struct sigaction	sigset;

	if (sigemptyset(&sigset.sa_mask) == -1)
		throw std::runtime_error("failed to empty signal mask");
	sigaddset(&sigset.sa_mask, SIGINT);
	sigset.sa_flags = SA_RESTART;
	sigset.sa_handler = &signalHandler;
	sigaction(SIGINT, &sigset, 0);
}



int	main(int ac, char **av)
{
	if (ac != 3)
	{
		std::cerr << "Expected command: /ircserv <port> <password>" << std::endl;
		return (1);
	}
	std::string	port = std::string(av[1]);
	std::string	password = std::string(av[2]);
	if (password.empty() || port.empty() || port.find_first_not_of("0123456789") != std::string::npos)
	{
		std::cerr << "Expected command: /ircserv <port> <password>" << std::endl;
		return (1);
	}
	try {
		setSignalHandler();
		Server server = Server(password);
		server.init(port);
		server.poll_events();
	} catch (std::exception& e) {
		std::cerr << e.what() << std::endl;
	}
	return (0);
}
