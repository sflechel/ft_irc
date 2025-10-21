#ifndef INVITE_HPP

# define INVITE_HPP

#include "Command.hpp"
#include "Server.hpp"
#include <string>
#include <vector>

class Invite : public Command
{
	public:
		Invite(Server& server, Client& user, std::string cmd_name, std::vector<std::string> params);
		~Invite(void);

		void	enactCommand(void);
	private:
		void	invite(Channel* channel, std::string to_invite);
};

#endif //INVITE_HPP
