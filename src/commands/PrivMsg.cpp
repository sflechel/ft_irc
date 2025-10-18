#include "commands/PrivMsg.hpp"
#include "Client.hpp"
#include "ResponseBuilder.hpp"
#include <unistd.h>
#include <iostream>

PrivMsg::PrivMsg(Server& server, Client& user, std::string cmd_name, std::vector<std::string> params) : Command(server, user, cmd_name, params)
{}

void    PrivMsg::enactCommand(void)
{
    ResponseBuilder respbldr = ResponseBuilder(_server.getName(), _user);
	if (_params.size() != 2)
        _user.setResponse(respbldr.buildResponseString(_cmd_name, ERR_NEEDMOREPARAMS));
	else
	{
		const std::string& target = _params.at(0);
		if (target[0] == '#')
		{
			//_server.getChannel()
		}
		else
		{
			Client* client = _server.getClient(target);
			if (client == NULL)
        		_user.setResponse(respbldr.buildResponseString(target, ERR_NOSUCHNICK));
			else
			{
				//set other client response
			}
		}
	}
}

PrivMsg::~PrivMsg(void)
{}

