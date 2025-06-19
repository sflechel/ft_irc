/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sflechel <sflechel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 13:39:56 by sflechel          #+#    #+#             */
/*   Updated: 2025/06/19 16:58:40 by sflechel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP

# define SERVER_HPP

#include <vector>
# define LISTEN_BACKLOG 5
# define MAX_EVENTS 10

# include <sys/socket.h>
# include <netinet/in.h>
# include <string>
# include "Handler_connection.hpp"

class Server
{
	public:
		Server(char *port, char *password);
		~Server();
	private:
		int					m_master_socket;
		int					m_epollfd;
		std::string			m_password;
		struct sockaddr_in	m_master_socket_address;
		unsigned int		m_master_socket_address_len;
		std::vector<Client>	m_clients;
		void				setup_master_socket(char *port);
		void				setup_poll();
		void				poll_events();
		Server(void)		{}
};

#endif //SERVER_HPP
