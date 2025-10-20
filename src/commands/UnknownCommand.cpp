#include "commands/UnknownCommand.hpp"
#include "Command.hpp"
#include "ResponseBuilder.hpp"
#include <string>
#include <vector>

UnknownCommand::UnknownCommand(Server& server, Client& user, std::string cmd_name, std::vector<std::string> params) : Command(server, user, cmd_name, params)
{}

void	UnknownCommand::enactCommand(void)
{
	ResponseBuilder respbldr = ResponseBuilder(_server.getName(), _user);
	_user.setResponse(respbldr.buildResponseNum(_cmd_name, ERR_UNKNOWNCOMMAND));
}

UnknownCommand::~UnknownCommand(void)
{}

