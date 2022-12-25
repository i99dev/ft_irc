/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pong.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oal-tena <oal-tena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 16:13:09 by oal-tena          #+#    #+#             */
/*   Updated: 2022/12/25 10:01:16 by oal-tena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/cmd/Pong.hpp"

ft::Pong::Pong()
{
    _name = "Pong";
    _description = "Pong the server";
    _usage = "/pong";
}

void ft::Pong::execute()
{
    //set ping
    _client->setPing(1);
}
