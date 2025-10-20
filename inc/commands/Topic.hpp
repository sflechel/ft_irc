#ifndef TOPIC_HPP

# define TOPIC_HPP

#include "Command.hpp"
#include "Server.hpp"
#include <string>
#include <vector>

class   Topic : public Command
{
    public:
        Topic(Server& server, Client& user, std::string cmd_name, std::vector<std::string> params);
        ~Topic(void);
        void    enactCommand(void);
};

#endif //TOPIC_HPP
