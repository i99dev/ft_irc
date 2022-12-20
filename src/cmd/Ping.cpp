/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ping.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oal-tena <oal-tena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 07:06:48 by oal-tena          #+#    #+#             */
/*   Updated: 2022/12/20 16:48:41 by oal-tena         ###   ########.fr       */
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
    std::cout << "Ping executed" << std::endl;
    _client->setPing(1);
    std::string pong =  "PONG :" + _client->getServerName() + "\r\n";
    if (send(_client->getSocket(), pong.c_str(), pong.size(), 0) == -1)
        throw std::runtime_error("Error sending PONG");
    else
    {
        std::cout << "ping sent count = " << _client->getPing() << std::endl;
    }
}