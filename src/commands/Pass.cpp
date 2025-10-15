#include "commands/Pass.hpp"
#include "Command.hpp"
#include "ResponseBuilder.hpp"
#include <string>
#include <vector>

Pass::Pass(Server& server, Client& user, std::string cmd_name, std::vector<std::string> params) : Command(server, user, cmd_name, params), _password(server.getPassword())
{
    if (_params.size() < 1)
    {
        _need_more_params = 1;
        return ;
    }
    _key = _params.at(0);
}

void    Pass::enactCommand(void)
{
    ResponseBuilder respbldr = ResponseBuilder(_server.getName(), _user);

    if (this->_need_more_params)
        _user.setResponse(respbldr.buildResponseString(_cmd_name, ERR_NEEDMOREPARAMS));
    else if (_user.getIsRegistered())
        _user.setResponse(respbldr.buildResponseString("", ERR_ALREADYREGISTERED));
    else if (_key != _password)
        _user.setResponse(respbldr.buildResponseString("", ERR_PASSWDMISMATCH));
    else
        _user.setIsRegistered(true);
}

Pass::~Pass(void)
{}
