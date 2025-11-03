#include "ResponseBuilder.hpp"
#include "Channel.hpp"
#include "Client.hpp"
#include <set>
#include <sstream>
#include <string>
#include <cstdlib>
#include <iostream>

ResponseBuilder::ResponseBuilder(std::string servername, Client& target) : _servername(servername), _target(target)
{
}

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
	std::string response = "";

	switch (code)
	{
		case RPL_WELCOME:
			response += "Welcome to the Internet Relay Network " + _target.getNickname() + "!" + _target.getUsername() + "@" + _servername;
			break;
		case RPL_NAMREPLY:
			break;
		case RPL_ENDOFNAMES:
			response += user_input + " :End of /WHO list.";
			break;
		case RPL_NOTOPIC:
			response += user_input + " :No topic is set";
			break;
		case RPL_TOPIC:
			response += user_input;
			break;
		case RPL_INVITING:
			response += user_input;
			break;
		case ERR_NOSUCHNICK:
			response += user_input + " :No such nick";
			break;
		case ERR_NOSUCHCHANNEL:
			response += user_input + " :No such channel";
			break;
		case ERR_PASSWDALREADYSENT:
			response += ":Password already sent";
			break;
		case ERR_UNKNOWNCOMMAND:
			response += user_input + " :Unknown command";
			break;
		case ERR_NONICKNAMEGIVEN:
			response += ":No nickname given";
			break;
		case ERR_ERRONEUSNICKNAME:
			response += user_input + " :Erroneous nickname";
			break;
		case ERR_NICKNAMEINUSE:
			response += user_input + " :Nickname is already in use";
			break;
		case ERR_USERNOTINCHANNEL:
			response += user_input + " :They aren't on that channel";
			break;
		case ERR_NOTONCHANNEL:
			response += user_input + " :You're not on that channel";
			break;
		case ERR_USERONCHANNEL:
			response += user_input + " :is already on channel";
			break;
		case ERR_NOTREGISTERED:
			response += ":You have not registered";
			break;
		case ERR_NEEDMOREPARAMS:
			response += user_input + " :Not enough parameters";
			break;
		case ERR_ALREADYREGISTERED:
			response += ":Unauthorized command (already registered)";
			break;
		case ERR_PASSWDMISMATCH:
			response += ":Password incorrect";
			break;
		case ERR_CHANNELISFULL:
			response += user_input + " :Cannot join channel (+l)";
			break;
		case ERR_INVITEONLYCHAN:
			response += user_input + " :Cannot join channel (+i)";
			break;
		case ERR_BADCHANNELKEY:
			response += user_input + " :Cannot join channel (+k)";
			break;
		case ERR_NOPASSWD:
			response += user_input + " :Password missing, use PASS to authenticate";
			break;
		case ERR_NOPRIVILEGES:
			response += ":Permission Denied- You're not an IRC operator";
			break;
		case ERR_CHANOPRIVSNEEDED:
			response += user_input + " :You're not channel operator";
			break;
	}
	return (response);
}

std::string ResponseBuilder::buildResponseNum(std::string user_input, e_numeric numeric)
{
	std::string response;

	response += (":" + _servername + " ");
	response += enumericToStringNumber(numeric) + " ";
	if (this->_target.getNickname().empty())
		response += "default ";
	else
		response += this->_target.getNickname() + " ";
	response += enumericToMessage(numeric, user_input);
	response += "\r\n";
	return (response);
}

std::string ResponseBuilder::buildResponse(std::string command, std::string param)
{
	std::string response =  ":" + _target.getNickname() + " ";
	response += command + " ";
	response += param;
	response += "\r\n";
	return (response);
}

std::string ResponseBuilder::buildNamReply(Channel& channel)
{
	std::string response;

	response += ":" + _servername + " ";
	response += enumericToStringNumber(RPL_NAMREPLY);
	response += " " + _target.getNickname() + " = " + channel.getName() + " ";
	response += ":";

	std::set<std::string>			users = channel.getUsers();
	std::set<std::string>::iterator	it;

	for (it = users.begin() ; it != users.end() ; it++)
		response += (channel.isUserOp(*it) ? "@" : "") + *it + " ";
	response += "\r\n";
	return (response);
}
