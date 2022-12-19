/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ping.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oal-tena <oal-tena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 07:06:48 by oal-tena          #+#    #+#             */
/*   Updated: 2022/12/20 00:32:00 by oal-tena         ###   ########.fr       */
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
    std::string ping = "PING :" + _server->getServerName() + "\r \n";
    send(_client->getSocket(), ping.c_str(), ping.size(), 0);
    
    //receive pong
    char buffer[1024];
    int bytes = recv(_client->getSocket(), buffer, 1024, 0);
    buffer[bytes] = '\0';
    std::string pong = buffer;
    if (pong.find("PONG") != std::string::npos)
        _client->setPing(true);
    else
        _client->setPing(false);
    
}