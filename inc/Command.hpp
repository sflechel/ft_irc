#ifndef COMMAND_HPP
# define COMMAND_HPP

#include "Server.hpp"
# include <string>
# include <vector>

class Command
{
	public:
		Command(Server& server, Client& user, std::vector<std::string> params);
		~Command(void);

        virtual void    enactCommand(void) = 0;
	protected:
        Server&                     _server;
        Client&                     _user;
        std::string                 _cmd_name;
		std::vector<std::string>	_params;
        bool                        _need_more_params;
};

#endif
