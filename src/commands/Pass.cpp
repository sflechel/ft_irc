#include "commands/Pass.hpp"
#include "Command.hpp"
#include "ResponseBuilder.hpp"
#include <string>
#include <vector>
#include <iostream>

Pass::Pass(Server& server, Client& user, std::string cmd_name, std::vector<std::string> params) : Command(server, user, cmd_name, params)
{
}

void	Pass::enactCommand(void)
{
	//_respbldr.buildResponseNum(_cmd_name, ERR_NEEDMOREPARAMS);

	if (_params.size() != 1)
	{
		std::cout << "TESTESTTSETSETSTETST" << std::endl;
		std::cout << _respbldr.buildResponseNum(_cmd_name, ERR_NEEDMOREPARAMS) << std::endl;
	}
	else if (_user.getIsRegistered())
	{
		//return ;
		_user.setResponse(_respbldr.buildResponseNum("", ERR_ALREADYREGISTERED));
	}
	//else if (_params.at(0) != _server.getPassword())
	//	_user.setResponse(_respbldr.buildResponseNum("", ERR_PASSWDMISMATCH));
	//else
	//	_user.setSentPassword(true);
}

Pass::~Pass(void)
{}
