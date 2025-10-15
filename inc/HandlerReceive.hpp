#ifndef HANDLER_RECEIVE_HPP
# define HANDLER_RECEIVE_HPP

#include <vector>
# define READ_BUFFER_SIZE 1024

# include "Client.hpp"
# include "Server.hpp"

class HandlerReceive
{
	public:
		HandlerReceive(Client& client, Server& server);
		~HandlerReceive(void);

		void	readClientRequest(void);
		void	splitResponseToCmds(void);
		void	execCmds(void);

	private:
		Client&	_client;
		Server& _server;
		std::vector<std::string> _full_cmds;
};

#endif // !HANDLER_RECEIVE_HPP
