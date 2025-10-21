#ifndef PART_HPP

# define PART_HPP

#include "Channel.hpp"
#include "Command.hpp"
#include "Server.hpp"
#include <string>
#include <vector>

class Part : public Command
{
	public:
		Part(Server& server, Client& user, std::string cmd_name, std::vector<std::string> params);
		~Part(void);
		void	enactCommand(void);
	private:
		void	part(Channel& channel);
};

#endif //PART_HPP
