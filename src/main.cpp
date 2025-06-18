/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sflechel <sflechel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 13:36:54 by sflechel          #+#    #+#             */
/*   Updated: 2025/06/18 09:08:21 by sflechel         ###   ########.fr       */
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
	Reactor reactor = Reactor(server);
	// reactor.polling_loop();
	} catch (std::runtime_error &e) {
		std::cerr << e.what() << std::endl;
	}
	return (0);
}
