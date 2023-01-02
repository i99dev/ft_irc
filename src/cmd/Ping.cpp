/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ping.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 07:06:48 by oal-tena          #+#    #+#             */
/*   Updated: 2023/01/01 20:30:03 by aaljaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/cmd/Ping.hpp"

ft::Ping::Ping()
{
    _name = "Ping";
    _description = "Ping the server";
    _usage = "/ping";
}

void ft::Ping::execute()
{
	if (_client)
	{
		std::cout << BBLU << "Ping executed" << DEFCOLO << std::endl;
		_client->setPing(1);
		std::string pong =  "PONG :" + _client->getServerName() + "\r\n";
		if (send(_client->getSocket(), pong.c_str(), pong.size(), 0) == -1)
			std::cout << "Error: send" << std::endl;
		else
		{
			std::cout << "ping sent count = " << _client->getPing() << std::endl;
		}
	}
}