/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cap.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oal-tena <oal-tena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 06:54:54 by oal-tena          #+#    #+#             */
/*   Updated: 2022/12/21 22:59:42 by oal-tena         ###   ########.fr       */
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
    std::cout << "Cap executed" << std::endl;
    // // //send to client
    std::string msg = "CAP * LS :multi-prefix sasl\r\n";
    if (send(_client->getSocket(), msg.c_str(), msg.size(), 0) == -1)
        std::cout << "Error: send" << std::endl;
    else
        std::cout << "CAP sent" << std::endl;
}