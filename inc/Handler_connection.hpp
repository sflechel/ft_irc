/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Handler_connection.hpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sflechel <sflechel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 15:20:00 by sflechel          #+#    #+#             */
/*   Updated: 2025/06/17 16:17:30 by sflechel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HANDLER_CONNECTION_HPP

# define HANDLER_CONNECTION_HPP

class Handler_connection
{
	public:
		Handler_connection(int master_sock);
		~Handler_connection();
		int	accept_connection();
	private:
		int	m_master_sock;

};

#endif // !HANDLER_CONNECTION_HPP
