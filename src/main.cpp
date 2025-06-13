/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sflechel <sflechel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 13:36:54 by sflechel          #+#    #+#             */
/*   Updated: 2025/06/13 14:33:53 by sflechel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"
#include <stdexcept>
#include <iostream>

int	main(void)
{
	try {
	Server server = Server("0.0.0.0", MY_PORT);
	} catch (std::runtime_error &e) {
		std::cerr << e.what() << std::endl;
	}
	return (0);
}
