/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edarnand <edarnand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 10:00:35 by edarnand          #+#    #+#             */
/*   Updated: 2025/07/01 18:59:01 by edarnand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"
#include <cstddef>
#include <iostream>
#include <sstream>
#include <sys/socket.h>

bool Command::is_valid_cmd()
{
	const size_t space_pos = m_cmd_str.find(' ');

	if (space_pos != std::string::npos)
		m_cmd = m_cmd_str.substr(0, space_pos);
	else
		m_cmd = m_cmd_str;
	//if m_cmd is a know cmd -> valid
	return (true);
}

void Command::parse_params()
{
	std::stringstream	ss(m_cmd_str);
	std::string			tmp;

	while (std::getline(ss, tmp, ' '))
	{
		if (tmp[0] == ':')
		{
			m_params.push_back(m_cmd_str.substr(1, std::string::npos));
			break ;
		}
		else if (!tmp.empty())
			m_params.push_back(tmp);
	}

	for (size_t i = 0; i < m_params.size(); i++)
	{
		std::cout << m_params[i];
		if (i + 1 != m_params.size())
			std::cout << '|';
	}
	std::cout << std::endl;
}

void Command::parse_cmd()
{
	if (m_cmd_str.compare("\r\n") == 0)
	{
		std::cout << "empty cmd" << std::endl;
		return ;
	}
	m_cmd_str.resize(m_cmd_str.size() - 2);
	std::cout << "cmd receved\n" << m_cmd_str << std::endl;

	const size_t space_pos = m_cmd_str.find(' ');
	if (space_pos != std::string::npos)
		m_cmd = m_cmd_str.substr(0, space_pos);
	else
		m_cmd = m_cmd_str;
	parse_params();
}

Command::Command(std::string cmd_str) : m_cmd_str(cmd_str)
{}

Command::Command()
{}

Command::~Command()
{}