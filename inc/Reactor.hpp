/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Reactor.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sflechel <sflechel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 10:25:10 by sflechel          #+#    #+#             */
/*   Updated: 2025/06/17 15:24:10 by sflechel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REACTOR_HPP

# define REACTOR_HPP

# define MAX_EVENTS 10

# include "server.hpp"
# include <sys/epoll.h>

class Reactor
{
	public:
		Reactor(Server server);
		~Reactor();
		void				polling_loop();
	private:
		Server				m_server;
		int					m_epollfd;
		struct epoll_event	m_poll_opts;
		struct epoll_event	m_events[MAX_EVENTS];
};

#endif // !REACTOR_HPP
