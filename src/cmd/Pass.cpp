/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 10:10:38 by aaljaber          #+#    #+#             */
/*   Updated: 2023/01/03 06:20:21 by aaljaber         ###   ########.fr       */
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
	if (_client)
	{		
		std::cout << BBLU << "Pass executed" << DEFCOLO << std::endl;
		if (_message->getParameter().size() == 1)
		{
			if (_server->CLIENTISBACK)
				return ;
			if (_client->PASSFlag == 1 || _client->ALREADYREGISTERED == 1)
			{
				_client->sendReply(ERR_ALREADYREGISTERED(_server->getServerName(), _client->getNickName()));	
				return ;
			}
			if (_message->getParameter()[0] == _server->password)
			{
				_client->PASSFlag++;
				_server->registerClient(_client);
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
}