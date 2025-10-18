#include "ResponseBuilder.hpp"
#include "Client.hpp"
#include <sstream>
#include <string>
#include <cstdlib>

ResponseBuilder::ResponseBuilder(const std::string& servername, Client& target) : _servername(servername), _target(target)
{}

ResponseBuilder::~ResponseBuilder(void) {}

std::string ResponseBuilder::enumericToStringNumber(e_numeric code)
{
    std::stringstream   output;

    if (code / 10 < 1)
        output << "00" << (int)code;
    else if (code / 100 < 1)
        output << "0" << (int)code;
    else
        output << (int)code;
    return (output.str());
}

std::string ResponseBuilder::enumericToMessage(e_numeric code, std::string user_input)
{
    std::string response = ":";

    switch (code)
    {
        case RPL_WELCOME:
            response += "Welcome to the Internet Relay Network " + _target.getNickname() + "!" + _target.getUsername() + "@" + _servername;
            break;
        case ERR_UNKNOWNCOMMAND:
            response += user_input + " :Unknown command";
            break;
        case ERR_NONICKNAMEGIVEN:
            response += ":No nickname given";
            break;
        case ERR_NICKNAMEINUSE:
            response += user_input + " :Nickname is already in use";
            break;
        case ERR_NEEDMOREPARAMS:
            response += user_input + "  :Not enough parameters";
            break;
        case ERR_ALREADYREGISTERED:
            response += ":Unauthorized command (already registered)";
            break;
        case ERR_PASSWDMISMATCH:
            response += ":Password incorrect";
            break;
    }
    return (response);
}

std::string ResponseBuilder::buildResponseString(std::string user_input, e_numeric numeric)
{
    std::stringstream response;

    response << (":" + _servername + " ");
    response << enumericToStringNumber(numeric) << " ";
    response << this->_target.getNickname() << " ";
    response << enumericToMessage(numeric, user_input);
    response << "\r\n";
    return (response.str());
}
