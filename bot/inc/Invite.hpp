#ifndef INVITE_HPP

# define INVITE_HPP

#include "Command.hpp"

class Invite : public Command
{
	public:
		Invite(std::string nickname, std::string sender, std::string cmd_name, std::vector<std::string> params);
		~Invite(void);

		void	enactCommand(int socket);
};

#endif //INVITE_HPP
