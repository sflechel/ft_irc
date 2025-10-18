#ifndef MODE_HPP
# define MODE_HPP

#include "Command.hpp"
#include "Server.hpp"

class   Mode : public Command
{
    public:
        Mode(Server& server, Client& user, std::string cmd_name, std::vector<std::string> params);
        ~Mode(void);
        void    enactCommand(void);
};

#endif //MODE_HPP
