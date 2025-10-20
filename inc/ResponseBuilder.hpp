#ifndef RESPONSEBUILDER_HPP

#define RESPONSEBUILDER_HPP

#include "Channel.hpp"
#include "Client.hpp"
#include <string>

typedef enum	numeric
{
	RPL_WELCOME = 1,
	RPL_NOTOPIC = 331,
	RPL_TOPIC = 332,
	RPL_INVITING = 341,
	RPL_NAMREPLY = 353,
	ERR_NOSUCHNICK = 401,
	ERR_NOSUCHCHANNEL = 403,
	ERR_UNKNOWNCOMMAND = 421,
	ERR_NONICKNAMEGIVEN = 431,
	ERR_NICKNAMEINUSE = 433,
	ERR_NOTONCHANNEL = 442,
	ERR_USERONCHANNEL = 443,
	ERR_NOTREGISTERED = 451,
	ERR_NEEDMOREPARAMS = 461,
	ERR_ALREADYREGISTERED = 462,
	ERR_PASSWDMISMATCH = 464,
	ERR_CHANNELISFULL = 471,
	ERR_INVITEONLYCHAN = 473,
	ERR_BADCHANNELKEY = 475,
	ERR_NOPRIVILEGES = 481,
	ERR_CHANOPRIVSNEEDED = 482
}	e_numeric;

class ResponseBuilder
{
	public:
		ResponseBuilder(const std::string& servername, Client& target);
		~ResponseBuilder(void);

		std::string	buildResponseNum(std::string user_input, e_numeric numeric);
		std::string	buildResponse(std::string command, std::string param);
		std::string	buildNamReply(Channel& channel);

	private:

		std::string	enumericToStringNumber(e_numeric code);
		std::string	enumericToMessage(e_numeric code, std::string user_input);

		const std::string&	_servername;
		Client&				_target;
};

#endif //RESPONSEBUILDER_HPP
