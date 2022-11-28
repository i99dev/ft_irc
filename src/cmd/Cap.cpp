/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cap.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oal-tena <oal-tena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 22:42:14 by oal-tena          #+#    #+#             */
/*   Updated: 2022/11/28 23:04:51 by oal-tena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/cmd/Cap.hpp"

ft::Cap::Cap(void)
{
    _name = "CAP";
    _description = "Client capability negotiation";
    _usage = "/cap <subcommand> [parameters]";
}

void ft::Cap::execute()
{
    std::cout << "Cap executed" << std::endl;
    _client->setNickName(_message->getParameter()[1].data());
    _client->setUserName(_message->getParameter()[3]);
    //cout
    std::cout << "Client 1 " << _client->getNickName() << " has joined the server" << std::endl;
    std::cout << "Client 2" << _client->getUserName() << " has joined the server" << std::endl;
}
