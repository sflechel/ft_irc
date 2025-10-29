#ifndef BOT_HPP

#define BOT_HPP

#include <string>
#include <vector>
#include "Command.hpp"

class Bot
{
	public:
		Bot(int port, std::string password, std::string nickname);
		~Bot();
		void	run(void);
		std::string	getPassword(void) const;
		std::string	getNickname(void) const;
	private:
		void		receivePacket(void);
		void		splitPacketToCmds(void);
		void		parseCmdParams(std::string& input, std::string& sender, std::vector<std::string>& params);
		void		execCmds(void);
		int							_port;
		int							_socket;
		std::string					_password;
		std::string					_nickname;
		std::string					_packet;
		std::vector<std::string>	_cmd_strings;
		std::vector<Command*>		_cmds;
};

#endif
