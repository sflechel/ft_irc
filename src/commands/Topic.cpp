#include "commands/Topic.hpp"
#include "Channel.hpp"
#include "Command.hpp"
#include <string>
#include <vector>
#include "ResponseBuilder.hpp"

Topic::Topic(Server& server, Client& user, std::string cmd_name, std::vector<std::string> params) : Command(server, user, cmd_name, params)
{}

void    Topic::enactCommand(void)
{
    ResponseBuilder respbldr = ResponseBuilder(_server.getName(), _user);

    int size = _params.size();
    if (size < 1 || size > 2)
        _user.setResponse(respbldr.buildResponseNum(_cmd_name, ERR_NEEDMOREPARAMS));
    else if (!_user.getIsRegistered())
        _user.setResponse(respbldr.buildResponseNum("", ERR_NOTREGISTERED));
    else if (size == 1)
    {
        Channel*    channel = _server.getChannel(_params.at(0));
        if (channel == NULL)
            _user.setResponse(respbldr.buildResponseNum("", RPL_NOTOPIC));
        else if (channel->getIsTopicRestricted())
            _user.setResponse(respbldr.buildResponseNum(channel->getName(), ERR_CHANOPRIVSNEEDED));
        else
            _user.setResponse(respbldr.buildResponseNum(channel->getName() + " :" + channel->getTopic(), RPL_TOPIC));
    }
    else 
    {
        Channel*    channel = _server.getChannel(_params.at(0));
        channel->setTopic(_params.at(1));
    }
}

Topic::~Topic(void)
{}
