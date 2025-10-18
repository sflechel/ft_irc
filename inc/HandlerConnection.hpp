#ifndef HANDLERCONNECTION_HPP
# define HANDLERCONNECTION_HPP

# include <Client.hpp>
# include <vector>

class HandlerConnection
{
	public:
		HandlerConnection(int masterSock);
		~HandlerConnection();

		Client* acceptConnection();
        void    registerClient(Client* newClient, std::vector<Client*>& listClients, int epollfd);
	private:
		int	_masterSock;

};

#endif // HANDLERCONNECTION_HPP
