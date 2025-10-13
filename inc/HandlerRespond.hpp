#ifndef HANDLER_RESPOND_HPP
# define HANDLER_RESPOND_HPP

# define READ_BUFFER_SIZE 1024

# include "Client.hpp"

class HandlerRespond
{
	public:
		HandlerRespond(Client& client);
		~HandlerRespond();
        void    respond(void);
	private:
		Client& _client;
};

#endif // !HANDLER_RESPOND_HPP
