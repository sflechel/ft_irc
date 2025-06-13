/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sflechel <sflechel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 13:39:56 by sflechel          #+#    #+#             */
/*   Updated: 2025/06/13 15:34:24 by sflechel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP

# define SERVER_HPP

# define MY_PORT 5000
# define LISTEN_BACKLOG 5

#include <string>
#include <sys/socket.h>
#include <netinet/in.h>

class Server
{
	public:
		Server(std::string ip_address, int port);
		~Server();
	private:
		std::string			m_ip_address;
		int					m_port;
		int					m_master_socket;
		struct sockaddr_in	m_master_socket_address;
		unsigned int		m_master_socket_address_len;
};

#endif //SERVER_HPP
