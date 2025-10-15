#ifndef PASS_HPP

# define PASS_HPP

#include "Command.hpp"
#include "Server.hpp"
#include <string>

class   Pass : public Command
{
    public:
        Pass(Server& server);
        ~Pass(void);
        void    enactCommand(void);
    private:
        std::string _password;
};

#endif //PASS_HPP
