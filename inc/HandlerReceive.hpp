#ifndef HANDLER_RECEIVE_HPP
# define HANDLER_RECEIVE_HPP

# define READ_BUFFER_SIZE 1024

# include "Client.hpp"
# include "Server.hpp"

class HandlerReceive
{
	public:
		HandlerReceive(Client& client, Server& server);
		~HandlerReceive(void);

		void	read_data_sent(void);
        void    runCommands(void);

	private:
		Client&	_client;
        Server& _server;
};

#endif // !HANDLER_RECEIVE_HPP
