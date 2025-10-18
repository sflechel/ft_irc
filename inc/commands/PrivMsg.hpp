#ifndef PRIVMSG_HPP
# define PRIVMSG_HPP

#include "Command.hpp"
#include "Server.hpp"

class   PrivMsg : public Command
{
    public:
        PrivMsg(Server& server, Client& user, std::string cmd_name, std::vector<std::string> params);
        ~PrivMsg(void);
        void    enactCommand(void);
};

#endif //PRIVMSG_HPP
