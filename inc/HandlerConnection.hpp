#ifndef HANDLERCONNECTION_HPP
# define HANDLERCONNECTION_HPP

# include "Client.hpp"
# include <set>

class HandlerConnection
{
	public:
		HandlerConnection(Server& server);
		~HandlerConnection();

		Client*	acceptConnection();
		void	registerClient(Client* newClient, std::set<Client*>& listClients, int epollfd);

	private:
		Server&	_server;

};

#endif // HANDLERCONNECTION_HPP
