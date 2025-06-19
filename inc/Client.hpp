/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sflechel <sflechel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 16:29:52 by sflechel          #+#    #+#             */
/*   Updated: 2025/06/19 16:56:00 by sflechel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string>

class Client{
	public:
		Client(int fd);
		~Client();
		int				get_my_fd();
	private:
		int				m_my_fd;
		bool			m_is_registered;
		std::string		m_nickname;
		std::string		m_username;
		Client(void)	{}
};
