/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sflechel <sflechel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 13:39:56 by sflechel          #+#    #+#             */
/*   Updated: 2025/06/19 15:18:40 by sflechel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP

# define SERVER_HPP

# define MY_PORT 5000
# define LISTEN_BACKLOG 5
# define MAX_EVENTS 10

# include <sys/socket.h>
# include <netinet/in.h>

class Server
{
	public:
		Server(int port);
		~Server();
	private:
		void				setup_master_socket();
		void				setup_poll();
		void				poll_events();
		Server(void)		{}
		int					m_master_socket;
		int					m_epollfd;
		int					m_port;
		struct sockaddr_in	m_master_socket_address;
		unsigned int		m_master_socket_address_len;
};

#endif //SERVER_HPP
