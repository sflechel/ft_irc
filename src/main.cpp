/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edarnand <edarnand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 13:36:54 by sflechel          #+#    #+#             */
/*   Updated: 2025/06/23 17:19:50 by edarnand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"
#include <cstdlib>
#include <stdexcept>
#include <iostream>

int	main(int ac, char **av)
{
	char	*port = av[1];
	char	*password = av[2];

	if (ac != 3)
	{
		std::cerr << "Expected command: /ircserv <port> <password>" << std::endl;
		return (1);
	}//TODO: protect port from non-ints
	try {
		Server server = Server(port, password);
	} catch (std::runtime_error &e) {
		std::cerr << e.what() << std::endl;
	}
	return (0);
}
