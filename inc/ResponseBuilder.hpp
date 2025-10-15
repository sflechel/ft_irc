#ifndef RESPONSEBUILDER_HPP

# define RESPONSEBUILDER_HPP

#include "Client.hpp"
# include <string>

typedef enum    numeric
{
    RPL_WELCOME = 1,
    RPL_YOURHOST = 2,
    RPL_CREATED = 3,
}   e_numeric;

class   ResponseBuilder
{
    public:
        ResponseBuilder(std::string& servername, e_numeric numeric, Client& target);
        ~ResponseBuilder(void);
        std::string     buildResponseString(void);
    private:
        std::string&    _servername;
        e_numeric       _numeric;
        Client&         _target;
};

#endif //RESPONSEBUILDER_HPP
