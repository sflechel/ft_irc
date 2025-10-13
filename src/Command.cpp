#include "Command.hpp"
#include <cstddef>
#include <iostream>
#include <sstream>
#include <sys/socket.h>

bool Command::is_valid_cmd()
{
	const size_t space_pos = _cmd_str.find(' ');

	if (space_pos != std::string::npos)
		_cmd = _cmd_str.substr(0, space_pos);
	else
		_cmd = _cmd_str;
	//if _cmd is a know cmd -> valid
	return (true);
}

void Command::parse_params()
{
	std::stringstream	ss(_cmd_str);
	std::string			tmp;

	while (std::getline(ss, tmp, ' '))
	{
		if (tmp[0] == ':')
		{
			_params.push_back(_cmd_str.substr(1, std::string::npos));
			break ;
		}
		else if (!tmp.empty())
			_params.push_back(tmp);
	}

	for (size_t i = 0; i < _params.size(); i++)
	{
		std::cout << _params[i];
		if (i + 1 != _params.size())
			std::cout << '|';
	}
	std::cout << std::endl;
}

void Command::parse_cmd()
{
	if (_cmd_str.compare("\r\n") == 0)
	{
		std::cout << "empty cmd" << std::endl;
		return ;
	}
	_cmd_str.resize(_cmd_str.size() - 2);
	std::cout << "cmd receved\n" << _cmd_str << std::endl;

	const size_t space_pos = _cmd_str.find(' ');
	if (space_pos != std::string::npos)
		_cmd = _cmd_str.substr(0, space_pos);
	else
		_cmd = _cmd_str;
	parse_params();
}

Command::Command(std::string cmd_str) : _cmd_str(cmd_str)
{}

Command::Command()
{}

Command::~Command()
{}