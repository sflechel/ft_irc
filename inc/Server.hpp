#ifndef SERVER_HPP

# define SERVER_HPP

# define LISTEN_BACKLOG 5
# define MAX_EVENTS 10

# include "Channel.hpp"
# include <sys/socket.h>
# include <netinet/in.h>
# include <string>
# include "Client.hpp"
# include <map>

class Server
{
	public:
		Server(std::string port, std::string password);
		~Server();

		//main loop
		void		poll_events(void);
		void		sendersToEpollOut(void);
		void		addSender(Client* client);
		void		removeSender(Client* client);

		//setters
		void		updateNickname(Client* client, std::string new_nickname);
		void		createChannel(std::string name, Client& user);
		void		registerClient(Client* client, std::string nickname);
		void		removeClient(std::string nickname);
		void		removeNewClient(Client* client);
		void		forceQuitClient(Client* client);

		//getters
		std::string							getPassword(void) const;
		std::string							getName(void) const;
		Client*								getClient(std::string nickname);
		std::set<Client*>&					getNewClients(void);
		std::map<std::string, Client*>&		getClients(void);
		Channel*							getChannel(std::string name);
		std::map<std::string, Channel*>&	getChannels(void);
		int									getMasterSocket(void) const;
		int									getEpollFd(void) const;

	private:
		int								_master_socket;
		int								_epollfd;
		std::string						_password;
		struct sockaddr_in				_master_socket_address;
		unsigned int					_master_socket_address_len;
		std::set<Client*>				_new_clients;
		std::map<std::string, Client*>	_clients;
		std::map<std::string, Channel*>	_channels;
		std::string						_name;
		std::set<Client*>				_senders;

		//setup
		void	setup_master_socket(std::string port);
		void	setup_poll(void);

		Server(void){}
};

#endif //SERVER_HPP
