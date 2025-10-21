#include "commands/Mode.hpp"
#include "Channel.hpp"
#include "Client.hpp"
#include "Server.hpp"
#include <sstream>
#include <string>

Mode::Mode(Server& server, Client& user, std::string cmd_name, std::vector<std::string> params) : Command(server, user, cmd_name, params)
{}

std::string	Mode::messageMode(void)
{
	std::string	msg = ":" + _user.getNickname() + " ";
	msg += "MODE " + _params.at(0);
	msg += " " + _params.at(1);
	if (_params.size() == 3)
		msg += " " + _params.at(2);
	msg += "\r\n";
	return msg;
}

bool	Mode::modeI(void)
{
	_channel->setIsInviteOnly(_sign == '+');
	return true;
}

bool	Mode::modeT(void)
{
	_channel->setIsTopicRestricted(_sign == '+');
	return true;
}

bool	Mode::modeK(void)
{
	if (_sign == '-')
		_channel->setKey("");
	else if (_params.size() == 3 && !_params.at(2).empty())
		_channel->setKey(_params.at(2));
	else
	{
		_user.addResponse(_respbldr.buildResponseNum(_cmd_name, ERR_NEEDMOREPARAMS));
		return false;
	}
	return true;
}

bool	Mode::modeO(void)
{
	const std::string target_chan = _params.at(0);

	if (_params.size() != 3)
	{
		_user.addResponse(_respbldr.buildResponseNum(_cmd_name, ERR_NEEDMOREPARAMS));
		return false;
	}
	const std::string& target_user = _params.at(2);
	if (!_server.getClient(target_user))
		_user.addResponse(_respbldr.buildResponseNum(target_user, ERR_NOSUCHNICK));
	else if (!_channel->isUserInChannel(target_user))
		_user.addResponse(_respbldr.buildResponseNum(target_user + " " + target_chan, ERR_USERNOTINCHANNEL));
	else
	{
		if (_sign == '-')
			_channel->removeOp(target_user);
		else
			_channel->addOp(target_user);
		return true;
	}
	return false;
}

bool	Mode::modeL(void)
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
	else
	{
		_user.addResponse(_respbldr.buildResponseNum(_cmd_name, ERR_NEEDMOREPARAMS));
		return false;
	}
	return true;
}

bool	Mode::choseMode(void)
{
	if (_mode == 'i')
		return (this->modeI());
	else if (_mode == 't')
		return (this->modeT());
	else if (_mode == 'k')
		return (this->modeK());
	else if (_mode == 'o')
		return (this->modeO());
	else if (_mode == 'l')
		return (this->modeL());
	return false;
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
			const std::string custom_err = ":" + _server.getName() + " 472 " + _user.getNickname() + " :" + mode + " :is invalid/unknown mode char to me for " + target_chan + "\r\n";

			if (mode.length() != 2 || (mode[0] != '-' && mode[0] != '+')
				|| (mode[1] != 'i' && mode[1] != 't' && mode[1] != 'k' && mode[1] != 'o' && mode[1] != 'l'))
				_user.addResponse(custom_err);
			else
			{
				_sign = mode[0];
				_mode = mode[1];
				if (choseMode())
				{
					std::string	msg = this->messageMode();
					_user.addResponse(msg);
					_channel->sendChannelMessage(msg, _user);
				}
			}
		}
	}
}

Mode::~Mode(void)
{}

