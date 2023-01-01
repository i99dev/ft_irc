/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 11:57:08 by aaljaber          #+#    #+#             */
/*   Updated: 2023/01/01 17:59:11 by aaljaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/cmd/Quit.hpp"

ft::Quit::Quit(void)
{
    _name =  "Quit";
    _description = "leave the server";
    _usage = "/quit";
}


void	ft::Quit::execute(void)
{
	if (_client)
	{		
		std::cout << "🔴 " << _client->getNickName() << " is leaving the server" << std::endl;
		_server->remove_fds(_client->fd);
		_server->removeClient(_client);
	}
}