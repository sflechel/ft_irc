/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sflechel <sflechel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 13:36:54 by sflechel          #+#    #+#             */
/*   Updated: 2025/06/17 16:35:43 by sflechel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"
#include "Reactor.hpp"
#include <stdexcept>
#include <iostream>

int	main(void)
{
	try {
	Server server = Server(MY_PORT);
	} catch (std::runtime_error &e) {
		std::cerr << e.what() << std::endl;
	}
	try {
	Reactor reactor = Reactor(server);
	} catch (std::runtime_error &e) {
		std::cerr << e.what() << std::endl;
	}
	return (0);
}
