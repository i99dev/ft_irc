/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pong.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 16:13:09 by oal-tena          #+#    #+#             */
/*   Updated: 2023/01/01 19:34:37 by aaljaber         ###   ########.fr       */
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
	if (_client)
    {
		std::cout << "Pong executed" << std::endl;
		_client->setPing(1);
	}
}
