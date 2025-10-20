#include "commands/PrivMsg.hpp"
#include "Channel.hpp"
#include "Client.hpp"
#include "ResponseBuilder.hpp"
#include <unistd.h>

PrivMsg::PrivMsg(Server& server, Client& user, std::string cmd_name, std::vector<std::string> params) : Command(server, user, cmd_name, params)
{}

void    PrivMsg::enactCommand(void)
{
    ResponseBuilder respbldr = ResponseBuilder(_server.getName(), _user);
	if (!_user.getIsRegistered())
		_user.setResponse(respbldr.buildResponseNum("", ERR_NOTREGISTERED));
	else if (_params.size() != 2 || _params.at(1).empty())
        _user.setResponse(respbldr.buildResponseNum(_cmd_name, ERR_NEEDMOREPARAMS));
	else
	{
		const std::string&	target = _params.at(0);
		const std::string	message_response = ":" + _user.getNickname() + " " + _cmd_name + " " + _params.at(0) + " " + _params.at(1) + "\r\n";

		if (target[0] == '#')
		{
			Channel* channel = _server.getChannel(target);
			if (channel == NULL)
        		_user.setResponse(respbldr.buildResponseNum(target, ERR_NOSUCHCHANNEL));
			else
			{
				channel->sendChannelMessage(message_response, _user);
			}
		}
		else
		{
			Client* client = _server.getClient(target);
			if (client == NULL)
        		_user.setResponse(respbldr.buildResponseNum(target, ERR_NOSUCHNICK));
			else
				client->setResponse(message_response);
		}
	}
}

PrivMsg::~PrivMsg(void)
{}

