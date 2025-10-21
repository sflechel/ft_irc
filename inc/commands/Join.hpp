#ifndef JOIN_HPP

# define JOIN_HPP

#include "Command.hpp"
#include <string>

class Join : public Command
{
	public:
		Join(Server& server, Client& user, std::string cmd_name, std::vector<std::string> params);
		~Join(void);

		void	joinMessage(Channel& channel);
		void	joinChannel(Channel& channel);
		void	joinChannel(Channel& channel, std::string name, std::string key);
		void	leaveAllChannels(void);
		void	createChannel(std::string name);
		void	enactCommand(void);
};

#endif //JOIN_HPP
