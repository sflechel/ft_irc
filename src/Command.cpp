#include "Command.hpp"
#include <string>
#include <sys/socket.h>
#include <unistd.h>
#include <vector>

Command::Command(Server& server, Client& user, std::string cmd_name, std::vector<std::string> params) :
	_server(server),
	_user(user),
	_cmd_name(cmd_name),
	_params(params),
	_need_more_params(0)
{}

Command::~Command()
{}
