#ifndef RESPONSEBUILDER_HPP

# define RESPONSEBUILDER_HPP

#include "Client.hpp"
# include <string>

typedef enum    numeric
{
    RPL_WELCOME = 1,
    ERR_NEEDMOREPARAMS = 461,
}   e_numeric;

class   ResponseBuilder
{
    public:
        ResponseBuilder(const std::string& servername, Client& target);
        ~ResponseBuilder(void);
        std::string     buildResponseString(std::string user_input, e_numeric numeric);
    private:
        
        std::string         enumericToStringNumber(e_numeric code);
        std::string         enumericToMessage(e_numeric code, std::string user_input);
        const std::string&  _servername;
        Client&             _target;
};

#endif //RESPONSEBUILDER_HPP
