#include "Server.hpp"
#include <csignal>
#include <cstdlib>
#include <stdexcept>
#include <iostream>
#include <signal.h>

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
	char	*port = av[1];
	char	*password = av[2];

	if (ac != 3)
	{
		std::cerr << "Expected command: /ircserv <port> <password>" << std::endl;
		return (1);
	}//TODO: protect port from non-ints
	try {
		setSignalHandler();
		Server server = Server(port, password);
	} catch (std::runtime_error &e) {
		std::cerr << e.what() << std::endl;
	}
	return (0);
}
