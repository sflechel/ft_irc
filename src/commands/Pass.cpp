#include "commands/Pass.hpp"
#include "Command.hpp"
#include "ResponseBuilder.hpp"
#include <string>
#include <vector>

Pass::Pass(Server& server, Client& user, std::string cmd_name, std::vector<std::string> params) : Command(server, user, cmd_name, params)
{}

void	Pass::enactCommand(void)
{
	if (_params.size() != 1)
		_user.addResponse(_respbldr.buildResponseNum(_cmd_name, ERR_NEEDMOREPARAMS));
	else if (_user.getIsRegistered())
		_user.addResponse(_respbldr.buildResponseNum("", ERR_ALREADYREGISTERED));
	else if (_user.getSentPassword())
		_user.addResponse(_respbldr.buildResponseNum("", ERR_PASSWDALREADYSENT));
	else if (_params.at(0) != _server.getPassword())
		_user.addResponse(_respbldr.buildResponseNum( "", ERR_PASSWDMISMATCH));
	else
		_user.setSentPassword(true);
}

Pass::~Pass(void)
{}
