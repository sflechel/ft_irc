#include "commands/Pass.hpp"
#include "Command.hpp"
#include "ResponseBuilder.hpp"
#include <string>
#include <vector>

Pass::Pass(Server& server, Client& user, std::vector<std::string> params) : Command(server, user, params), _password(server.getPassword())
{
    _cmd_name = "Pass";
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
    {
        _user.setResponse(respbldr.buildResponseString(_cmd_name, ERR_NEEDMOREPARAMS));
        return ;
    }
}

Pass::~Pass(void)
{}
