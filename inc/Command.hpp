/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edarnand <edarnand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 10:00:52 by edarnand          #+#    #+#             */
/*   Updated: 2025/07/01 18:58:29 by edarnand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MESSAGE_HPP
# define MESSAGE_HPP

# include <string>
# include <vector>

class Command
{
	public:
		void	parse_cmd();
		bool	is_valid_cmd();
		Command();
		Command(std::string cmd_str);
		~Command();
	private:
		std::string					m_cmd_str;
		std::string					m_cmd;
		std::vector<std::string>	m_params;

		void parse_params();
};

#endif
