#ifndef HANDLER_RECEIVE_HPP
# define HANDLER_RECEIVE_HPP

#include <vector>
# define READ_BUFFER_SIZE 1024

# include "Client.hpp"
# include "Command.hpp"
# include "Server.hpp"

class HandlerReceive
{
	public:
		HandlerReceive(Client& client, Server& server);
		~HandlerReceive(void);

		int		readClientRequest(void);
		void	splitResponseToCmds(void);
		void	parseCmdParam(std::string &input, std::vector<std::string>& vec);
		void	execCmds(void);

	private:
		Client&	_client;
		Server& _server;
		std::vector<std::string>	_full_cmds;
		std::vector<Command*>		_cmds;

};

#endif // !HANDLER_RECEIVE_HPP
