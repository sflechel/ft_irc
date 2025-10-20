#ifndef PASS_HPP

# define PASS_HPP

#include "Command.hpp"
#include "Server.hpp"
#include <string>
#include <vector>

class Pass : public Command
{
	public:
		Pass(Server& server, Client& user, std::string cmd_name, std::vector<std::string> params);
		~Pass(void);

		void	enactCommand(void);
};

#endif //PASS_HPP
