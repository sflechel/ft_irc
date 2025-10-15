#ifndef NICK_HPP

# define NICK_HPP

#include "Command.hpp"
#include "Server.hpp"
#include <string>
#include <vector>

class   Nick : public Command
{
    public:
        Nick(Server& server, Client& user, std::string cmd_name, std::vector<std::string> params);
        ~Nick(void);
        void    enactCommand(void);
};

#endif //NICK_HPP
