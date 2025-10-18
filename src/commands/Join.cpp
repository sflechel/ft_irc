#include "commands/Join.hpp"
#include "Channel.hpp"
#include "Command.hpp"
#include "ResponseBuilder.hpp"
#include "Server.hpp"
#include <cstddef>
#include <map>
#include <string>
#include <vector>

Join::Join(Server& server, Client& user, std::string cmd_name, std::vector<std::string> params) : Command(server, user, cmd_name, params)
{}

Join::~Join(void)
{}

void    Join::joinChannel(std::string name)
{
    ResponseBuilder respbldr = ResponseBuilder(_server.getName(), _user);

    if (name.size() < 2 || name.at(0) != '#')
    {
        _user.setResponse(respbldr.buildResponseNum(name, ERR_NOSUCHCHANNEL));
        return ;
    }
    Channel*    channel = _server.getChannel(name);
    if (channel == NULL)
        _server.createChannel(name, _user);
    else
        channel->addUser(_user.getNickname());
    _user.setResponse(respbldr.buildResponse("JOIN", name));
}

void    Join::joinChannel(std::string name, std::string key)
{
    ResponseBuilder respbldr = ResponseBuilder(_server.getName(), _user);

    if (name.size() < 2 || name.at(0) != '#')
    {
        _user.setResponse(respbldr.buildResponseNum(name, ERR_NOSUCHCHANNEL));
        return ;
    }
    Channel*    channel = _server.getChannel(name);
    if (channel == NULL)
    {
        _server.createChannel(name, _user);
        _user.setResponse(respbldr.buildResponse("JOIN", name));
        return ;
    }
    if (key == channel->getKey())
    {
        channel->addUser(_user.getNickname());
        _user.setResponse(respbldr.buildResponse("JOIN", name));
    }
    else
        _user.setResponse(respbldr.buildResponseNum(name, ERR_BADCHANNELKEY));
}

void    Join::enactCommand(void)
{
    ResponseBuilder respbldr = ResponseBuilder(_server.getName(), _user);

    int size = _params.size();
    if (size < 1 || size > 2)
        _user.setResponse(respbldr.buildResponseNum(_cmd_name, ERR_NEEDMOREPARAMS));
    else if (_params.at(0) == "0")
    {
        std::map<std::string, Channel*>  channels = _server.getChannels();
        std::map<std::string, Channel*>::iterator   it;
        for (it = channels.begin() ; it != channels.end() ; it++)
        {
            it->second->leave(_user.getNickname());
        }
    }
    else
    {
        if (size == 1)
            joinChannel(_params.at(0));
        else
            joinChannel(_params.at(0), _params.at(1));
    }

}
