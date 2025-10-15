#ifndef UNKNOWNCOMMAND_HPP

# define UNKNOWNCOMMAND_HPP

#include "Command.hpp"
#include "Server.hpp"
#include <string>
#include <vector>

class   UnknownCommand : public Command
{
    public:
        UnknownCommand(Server& server, Client& user, std::string cmd_name, std::vector<std::string> params);
        ~UnknownCommand(void);
        void    enactCommand(void);
};

#endif //UNKNOWNCOMMAND_HPP
