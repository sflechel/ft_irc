#ifndef QUIT_HPP

# define QUIT_HPP

#include "Command.hpp"
#include "Server.hpp"
#include <string>
#include <vector>

class Quit : public Command
{
	public:
		Quit(Server& server, Client& user, std::string cmd_name, std::vector<std::string> params);
		~Quit(void);
		void	enactCommand(void);
};

#endif //QUIT_HPP
