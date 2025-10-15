#include "commands/User.hpp"
#include "Command.hpp"
#include "ResponseBuilder.hpp"
#include <string>
#include <vector>

User::User(Server& server, Client& user, std::string cmd_name, std::vector<std::string> params) : Command(server, user, cmd_name, params)
{
    if (_params.size() < 4)
    {
        _need_more_params = 1;
        return ;
    }
}

void    User::enactCommand(void)
{
    ResponseBuilder respbldr = ResponseBuilder(_server.getName(), _user);

    if (_need_more_params)
    {
        _user.setResponse(respbldr.buildResponseString(_cmd_name, ERR_NEEDMOREPARAMS));
        return ;
    }
    if (_user.getIsRegistered())
    {
        _user.setResponse(respbldr.buildResponseString("", ERR_ALREADYREGISTERED));
        return ;
    }
    _user.setUsername(_params.at(0));
    _user.setRealname(_params.at(3));
    _user.setResponse(respbldr.buildResponseString("", RPL_WELCOME));
}

User::~User(void)
{}
