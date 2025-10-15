#include "commands/Nick.hpp"
#include "Command.hpp"
#include "ResponseBuilder.hpp"
#include <cstddef>
#include <string>
#include <vector>

Nick::Nick(Server& server, Client& user, std::string cmd_name, std::vector<std::string> params) : Command(server, user, cmd_name, params)
{
    if (_params.size() < 1)
    {
        _need_more_params = 1;
        return ;
    }
}

void    Nick::enactCommand(void)
{
    ResponseBuilder respbldr = ResponseBuilder(_server.getName(), _user);
    if (!_user.getSentPassword())
        _user.setResponse(respbldr.buildResponseString("", ERR_PASSWDMISMATCH));
    else if (_need_more_params || _params.at(0).empty())
        _user.setResponse(respbldr.buildResponseString(_cmd_name, ERR_NONICKNAMEGIVEN));
    else if (_server.getClient(_params.at(0)) != NULL)
        _user.setResponse(respbldr.buildResponseString(_params.at(0), ERR_NICKNAMEINUSE));
    else
    {
        _user.setNickname(_params.at(0));

        if (!_user.getUsername().empty() && !_user.getIsRegistered())
        {
            _user.setResponse(respbldr.buildResponseString("", RPL_WELCOME));
            _user.setIsRegistered(true);
        }
    }
}

Nick::~Nick(void)
{}
