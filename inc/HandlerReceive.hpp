#ifndef HANDLER_RECEIVE_HPP
# define HANDLER_RECEIVE_HPP

# define READ_BUFFER_SIZE 1024

# include "Client.hpp"

class HandlerReceive
{
	public:
		HandlerReceive(Client client);
		~HandlerReceive();

		void	read_data_sent();

	private:
		Client	_client;
};

#endif // !HANDLER_RECEIVE_HPP
