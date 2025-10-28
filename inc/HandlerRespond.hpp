#ifndef HANDLER_RESPOND_HPP
# define HANDLER_RESPOND_HPP

# include "Client.hpp"
# include "Server.hpp"

class HandlerRespond
{
	public:
		HandlerRespond(Client& client, Server& server);
		~HandlerRespond();

		void	respond(void);

	private:
		void	removeClientFromSenders(void);
		Client& _client;
		Server&	_server;
};

#endif // !HANDLER_RESPOND_HPP
