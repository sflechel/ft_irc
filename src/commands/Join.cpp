#include "commands/Join.hpp"
#include "Command.hpp"
#include "ResponseBuilder.hpp"
#include "Server.hpp"
#include <string>
#include <vector>

Join::Join(Server& server, Client& user, std::string cmd_name, std::vector<std::string> params) : Command(server, user, cmd_name, params)
{}

Join::~Join(void)
{}

void    Join::joinChannel(std::string name)
{
}

void    Join::enactCommand(void)
{
    ResponseBuilder respbldr = ResponseBuilder(_server.getName(), _user);

    if (_params.empty())
        _user.setResponse(respbldr.buildResponseString(_cmd_name, ERR_NEEDMOREPARAMS));
    else if (_params.at(0) == "0")
    {}
}
