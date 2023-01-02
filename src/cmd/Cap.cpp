/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cap.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 06:54:54 by oal-tena          #+#    #+#             */
/*   Updated: 2023/01/01 20:28:29 by aaljaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/cmd/Cap.hpp"

ft::Cap::Cap()
{
    _name = "Cap";
    _description = "Client capability negotiation";
    _usage = "/cap <subcommand> [<subcommand> ...]";
}

void ft::Cap::execute()
{
	if (_client)
	{		
		std::cout << BBLU << "Cap executed" << DEFCOLO << std::endl;
		// // //send to client
		std::string msg = "CAP * LS :multi-prefix sasl\r\n";
		if (send(_client->getSocket(), msg.c_str(), msg.size(), 0) == -1)
			std::cout << "Error: send" << std::endl;
		else
			std::cout << "CAP sent" << std::endl;
	}
}