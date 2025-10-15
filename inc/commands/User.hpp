#ifndef USER_HPP

# define USER_HPP

#include "Command.hpp"
#include "Server.hpp"
#include <string>
#include <vector>

class   User : public Command
{
    public:
        User(Server& server, Client& user, std::string cmd_name, std::vector<std::string> params);
        ~User(void);
        void    enactCommand(void);
};

#endif //USER_HPP
