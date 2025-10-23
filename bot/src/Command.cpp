#include "Command.hpp"

Command::Command(std::string nickname, std::string sender, std::string cmd_name, std::vector<std::string> params) :
	_nickname(nickname),
	_sender(sender),
	_cmd_name(cmd_name),
	_params(params)
{}

Command::~Command()
{}
