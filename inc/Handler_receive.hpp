/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Handler_receive.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edarnand <edarnand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 16:56:00 by sflechel          #+#    #+#             */
/*   Updated: 2025/06/20 10:50:26 by edarnand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HANDLER_RECEIVE_HPP

# define HANDLER_RECEIVE_HPP
# define READ_BUFFER_SIZE 1024
class Handler_receive
{
	public:
		Handler_receive(int sock_fd);
		~Handler_receive();
		void	read_data_sent();
	private:
		void	parse_client_msg(char *msg, int msg_len);
		int		m_sock_fd;
};

#endif // !HANDLER_RECEIVE_HPP
