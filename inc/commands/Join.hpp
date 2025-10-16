#ifndef JOIN_HPP

# define JOIN_HPP

#include "Command.hpp"
#include <string>

class   Join : public Command
{
    public:
        Join(Server& server, Client& user, std::string cmd_name, std::vector<std::string> params);
        ~Join(void);
        void    joinChannel(std::string name);
        void    enactCommand(void);
};

#endif //JOIN_HPP
