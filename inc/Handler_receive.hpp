/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Handler_receive.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sflechel <sflechel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 16:56:00 by sflechel          #+#    #+#             */
/*   Updated: 2025/06/17 17:11:21 by sflechel         ###   ########.fr       */
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
		int		m_sock_fd;
};

#endif // !HANDLER_RECEIVE_HPP
