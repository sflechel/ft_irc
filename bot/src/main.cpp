#include "Bot.hpp"
#include <exception>
#include <iostream>
#include <sstream>
#include <string>
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
	sigset.sa_flags = 0;
	sigset.sa_handler = &signalHandler;
	sigaction(SIGINT, &sigset, 0);
}

int	main(int ac, char **av)
{
	if (ac != 4)
	{
		std::cerr << "Expected command: /bot <port> <server_password> <bot_nickname>" << std::endl;
		return 1;
	}

	std::string	port_str = std::string(av[1]);
	std::string	password = std::string(av[2]);
	std::string	nickname = std::string(av[3]);
	if (password.empty() || nickname.empty() || port_str.empty() || port_str.find_first_not_of("0123456789") != std::string::npos)
	{
		std::cerr << "Expected command: /bot <port> <server_password> <bot_nickname>" << std::endl;
		return (1);
	}

	int					port;
	std::istringstream	stream(port_str);
	stream >> port;

	try {
		setSignalHandler();
		Bot	bot = Bot(port, password, nickname);
		bot.run();
	} catch (std::exception& e) {
		std::cerr << e.what() << std::endl;
	}
	return 0;
}
