#ifndef RESPONSEBUILDER_HPP

# define RESPONSEBUILDER_HPP

#include "Client.hpp"
# include <string>

typedef enum    numeric
{
    RPL_WELCOME = 1,
	ERR_NOSUCHNICK = 401,
    ERR_NOSUCHCHANNEL = 403,
    ERR_UNKNOWNCOMMAND = 421,
    ERR_NONICKNAMEGIVEN = 431,
    ERR_NICKNAMEINUSE = 433,
	ERR_NOTREGISTERED = 451,
    ERR_NEEDMOREPARAMS = 461,
    ERR_ALREADYREGISTERED = 462,
    ERR_PASSWDMISMATCH = 464,
    ERR_BADCHANNELKEY = 475,
	ERR_NOPRIVILEGES = 481,
}   e_numeric;

class   ResponseBuilder
{
    public:
        ResponseBuilder(const std::string& servername, Client& target);
        ~ResponseBuilder(void);

        std::string     buildResponseNum(std::string user_input, e_numeric numeric);
        std::string     buildResponse(std::string command, std::string param);
    private:

        std::string         enumericToStringNumber(e_numeric code);
        std::string         enumericToMessage(e_numeric code, std::string user_input);

		const std::string&  _servername;
        Client&             _target;
};

#endif //RESPONSEBUILDER_HPP
