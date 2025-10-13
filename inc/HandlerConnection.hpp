#ifndef HANDLERCONNECTION_HPP
# define HANDLERCONNECTION_HPP

# include <Client.hpp>

class HandlerConnection
{
	public:
		HandlerConnection(int master_sock);
		~HandlerConnection();

		Client	accept_connection();

	private:
		int	_master_sock;

};

#endif // HANDLERCONNECTION_HPP
