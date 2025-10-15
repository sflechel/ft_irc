#include "Command.hpp"
#include <sys/socket.h>
#include <unistd.h>
#include <vector>

Command::Command(Server& server, Client& user, std::vector<std::string> params) : _params(params), _server(server), _user(user), _need_more_params(0)
{}

Command::~Command()
{}
