#ifndef SERVER_HPP

# define SERVER_HPP

# define LISTEN_BACKLOG 5
# define MAX_EVENTS 10

# include "Channel.hpp"
# include <sys/socket.h>
# include <netinet/in.h>
# include <string>
# include "Client.hpp"
# include <vector>
# include <map>

class Server
{
	public:
		Server(char *port, char *password);
		~Server();

		std::string	getPassword(void) const;
		void		updateNickname(Client* client, std::string new_nickname);
		void		createChannel(std::string name, Client& user);
		void		registerClient(Client* client, std::string nickname);
		void		removeClient(std::string nickname);
		void		removeNewClient(int index);
		void		forceQuitClient(Client* Client);

		std::string							getName(void) const;
		Client*								getClient(std::string nickname);
		std::vector<Client*>&				getNewClients(void);
		std::map<std::string, Client*>&		getClients(void);
		Channel*							getChannel(std::string name);
		std::map<std::string, Channel*>&	getChannels(void);

	private:
		int								_master_socket;
		int								_epollfd;
		std::string						_password;
		struct sockaddr_in				_master_socket_address;
		unsigned int					_master_socket_address_len;
		std::vector<Client*>			_new_clients;
		std::map<std::string, Client*>	_clients;
		std::map<std::string, Channel*>	_channels;
		std::string						_name;

		void	setup_master_socket(char *port);
		void	setup_poll();
		void	poll_events();

		Server(void){}
};

#endif //SERVER_HPP
