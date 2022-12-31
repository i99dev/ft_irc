/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 10:10:38 by aaljaber          #+#    #+#             */
/*   Updated: 2022/12/31 16:25:11 by aaljaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/cmd/Pass.hpp"

ft::Pass::Pass()
{
    _name = "pass";
    _description = "";
    _usage = "";
}

void ft::Pass::execute()
{
    std::cout << "Pass executed" << std::endl;
	if (_message->getParameter().size() == 1)
	{
		if (_server->CLIENTISBACK)
			return;
		if (_client->PASSFlag == 1)
		{
			_client->sendReply(ERR_ALREADYREGISTERED(_server->getServerName(), _client->getNickName()));	
			return ;
		}
		// std::cout << "server password " << _server->password << std::endl;
		// std::cout << "pass received " << _message->getParameter()[0] << std::endl;
		if (_message->getParameter()[0] == _server->password)
		{
			_client->PASSFlag++;
			std::cout << BGRN << "Correct password" << DEFCOLO << std::endl;
		}
		else
		{
			_client->sendReply(ERR_PASSWDMISMATCH(_server->getServerName(), _client->getNickName()));
			std::cout << BRED << "Wrong password" << DEFCOLO << std::endl;
		}
	}
	else
		_client->sendReply(ERR_NEEDMOREPARAMS(_server->getServerName(), _client->getNickName(), _message->getCommand()));	
}