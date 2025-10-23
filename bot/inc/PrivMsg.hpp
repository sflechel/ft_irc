#ifndef PRIVMSG_HPP
# define PRIVMSG_HPP

#include "Command.hpp"

class PrivMsg : public Command
{
	public:
		PrivMsg(std::string nickname, std::string sender, std::string cmd_name, std::vector<std::string> params);
		~PrivMsg(void);

		void	enactCommand(int socket);
};

#endif //PRIVMSG_HPP
