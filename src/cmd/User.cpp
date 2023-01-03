/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 19:18:38 by oal-tena          #+#    #+#             */
/*   Updated: 2023/01/02 20:30:19 by aaljaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/cmd/User.hpp"

ft::User::User()
{
    _name = "User";
    _description = "Set username";
    _usage = "/user <username>";
}

void ft::User::execute()
{
	if (_client)
	{
		std::cout << BBLU << "User executed" << DEFCOLO << std::endl;
		if (_server->CLIENTISBACK)
		{
			_server->CLIENTISBACK = false;
			return;
		}
		if (_client->USERflag == 1)
		{
			_client->sendReply(ERR_ALREADYREGISTERED(_server->getServerName(), _client->getNickName()));
			return;	
		}
		if (_message->getParameter().size() != 4)
		{
			_client->sendReply(ERR_NEEDMOREPARAMS(_server->getServerName(), _client->getNickName(), _message->getCommand()));
			return;
		}
		if (_client->USERflag == 0)
		{
			_client->setUserName(_message->getParameter()[0]);
			_client->setHostName(_message->getParameter()[1]);
			_client->setServerName(_message->getParameter()[2]);
			_client->setRealName(_message->getParameter()[3]);
			_client->USERflag++;
			_server->registerClient(_client);
		}
	}
}