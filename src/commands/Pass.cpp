#include "commands/Pass.hpp"
#include "Command.hpp"
#include "ResponseBuilder.hpp"
#include <string>
#include <vector>

Pass::Pass(Server& server, Client& user, std::string cmd_name, std::vector<std::string> params) : Command(server, user, cmd_name, params), _password(server.getPassword())
{
    _key = _params.at(0);
}

void    Pass::enactCommand(void)
{
    ResponseBuilder respbldr = ResponseBuilder(_server.getName(), _user);

    if (_params.empty())
        _user.setResponse(respbldr.buildResponseString(_cmd_name, ERR_NEEDMOREPARAMS));
    else if (_user.getIsRegistered())
        _user.setResponse(respbldr.buildResponseString("", ERR_ALREADYREGISTERED));
    else if (_key != _password)
        _user.setResponse(respbldr.buildResponseString("", ERR_PASSWDMISMATCH));
    else
        _user.setSentPassword(true);
}

Pass::~Pass(void)
{}
