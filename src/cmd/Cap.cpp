/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cap.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oal-tena <oal-tena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 06:54:54 by oal-tena          #+#    #+#             */
/*   Updated: 2022/12/20 16:44:04 by oal-tena         ###   ########.fr       */
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
        throw std::runtime_error("Error sending CAP");
    else
        std::cout << "CAP sent" << std::endl;
}