/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Handler_receive.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edarnand <edarnand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 16:56:00 by sflechel          #+#    #+#             */
/*   Updated: 2025/06/25 11:15:03 by edarnand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HANDLER_RECEIVE_HPP

# include "Client.hpp"

# define HANDLER_RECEIVE_HPP
# define READ_BUFFER_SIZE 1024

class Handler_receive
{
	public:
		Handler_receive(Client client);
		~Handler_receive();
		void	read_data_sent();
	private:
		void	handle_client_msg(std::string msg);
		int		m_sock_fd;
		Client	m_client;
};

#endif // !HANDLER_RECEIVE_HPP
