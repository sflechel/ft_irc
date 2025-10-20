#ifndef KICK_HPP

# define KICK_HPP

#include "Channel.hpp"
#include "Command.hpp"
#include "Server.hpp"
#include <string>
#include <vector>

class Kick : public Command
{
	public:
		Kick(Server& server, Client& user, std::string cmd_name, std::vector<std::string> params);
		~Kick(void);

		void	kick(Channel& channel, std::string to_kick);
		void	enactCommand(void);
};

#endif //KICK_HPP
