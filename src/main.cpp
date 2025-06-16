/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sflechel <sflechel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 13:36:54 by sflechel          #+#    #+#             */
/*   Updated: 2025/06/16 17:42:07 by sflechel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"
#include <stdexcept>
#include <iostream>

int	main(void)
{
	try {
	Server server = Server(MY_PORT);
	} catch (std::runtime_error &e) {
		std::cerr << e.what() << std::endl;
	}
	return (0);
}
