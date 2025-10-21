#include "commands/Mode.hpp"
#include "Channel.hpp"
#include "Client.hpp"
#include "Server.hpp"
#include <sstream>

Mode::Mode(Server& server, Client& user, std::string cmd_name, std::vector<std::string> params) : Command(server, user, cmd_name, params)
{}

void	Mode::choseMode(void)
{
	const std::string target_chan = _params.at(0);

	if (_mode == 'i')
		_channel->setIsInviteOnly(_sign == '+');
	else if (_mode == 't')
		_channel->setIsTopicRestricted(_sign == '+');
	else if (_mode == 'k')
	{
		if (_sign == '-')
			_channel->setKey("");
		else if (_params.size() == 3)
			_channel->setKey(_params.at(2));
	}
	else if (_mode == 'o' && _params.size() == 3)
	{
		const std::string& target_user = _params.at(2);
		if (!_channel->isUserInChannel(target_user))
			_user.addResponse(_respbldr.buildResponseNum(target_user + " " + target_chan, ERR_USERNOTINCHANNEL));
		else if (_sign == '-')
			_channel->removeOp(target_user);
		else
			_channel->addOp(target_user);
	}
	else if (_mode == 'l')
	{
		if (_sign == '-')
			_channel->setUserLimit(-1);
		else if (_params.size() == 3)
		{
			std::istringstream ss(_params.at(2));
			int limit = -1;
			ss >> limit;
			if (limit > 0)
				_channel->setUserLimit(limit);
		}
	}
}

void	Mode::enactCommand(void)
{
	if (!_user.getIsRegistered())
		_user.addResponse(_respbldr.buildResponseNum("", ERR_NOTREGISTERED));
	else if (_params.size() < 2 || _params.size() > 3 || (_params.size() == 3 && _params.at(2).empty()))
		_user.addResponse(_respbldr.buildResponseNum(_cmd_name, ERR_NEEDMOREPARAMS));
	else
	{
		const std::string& target_chan = _params.at(0);
		const std::string& op_nick = _user.getNickname();
		_channel = _server.getChannel(target_chan);
		if (_channel == NULL)
			_user.addResponse(_respbldr.buildResponseNum(target_chan, ERR_NOSUCHCHANNEL));
		else if (!_channel->isUserInChannel(op_nick))
			_user.addResponse(_respbldr.buildResponseNum(target_chan, ERR_NOTONCHANNEL));
		else if (!_channel->isUserOp(op_nick))
			_user.addResponse(_respbldr.buildResponseNum(target_chan, ERR_NOPRIVILEGES));
		else
		{
			const std::string mode = _params.at(1);
			const std::string custom_err = ":" + _server.getName() + " 472 " + _user.getNickname() + " " + mode + " :is invalid/unknown mode char to me for " + target_chan + "\r\n";

			if (mode.length() != 2 || (mode[0] != '-' && mode[0] != '+')
				|| (mode[1] != 'i' && mode[1] != 't' && mode[1] != 'k' && mode[1] != 'o' && mode[1] != 'l'))
				_user.addResponse(custom_err);
			else
			{
				_sign = mode[0];
				_mode = mode[1];
				choseMode();
			}
		}
	}
}

Mode::~Mode(void)
{}

