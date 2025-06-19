/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sflechel <sflechel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 16:42:13 by sflechel          #+#    #+#             */
/*   Updated: 2025/06/19 18:10:04 by sflechel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"

int	Client::get_my_fd()
{
	return (this->m_my_fd);
}

Client::Client(int fd) : m_my_fd(fd)
{
	this->m_nickname = std::string();
	this->m_username = std::string();
	this->m_is_registered = false;
}

Client::~Client() {}
