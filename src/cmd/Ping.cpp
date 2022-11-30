/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ping.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oal-tena <oal-tena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 07:06:48 by oal-tena          #+#    #+#             */
/*   Updated: 2022/11/30 10:14:52 by oal-tena         ###   ########.fr       */
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
}