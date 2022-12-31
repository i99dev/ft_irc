/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 19:18:38 by oal-tena          #+#    #+#             */
/*   Updated: 2022/12/30 21:41:42 by aaljaber         ###   ########.fr       */
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
	std::cout << "User executed" << std::endl;
	if (_client)
	{
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
			_client->setUserName(_message->getParameter()[0]);
			_client->setHostName(_message->getParameter()[1]);
			_client->setServerName(_message->getParameter()[2]);
			_client->setRealName(_message->getParameter()[3]);
			_client->USERflag++;
			if (_client->PASSFlag == 1 && _client->NICKflag == 1 && _client->USERflag == 1)
			{
				std::string msg = RPL_WELCOME(_server->getServerName(), _client->getNickName());
				_server->sendReply(_client, msg);
				msg = RPL_YOURHOST(_server->getServerName(), _client->getNickName(), _server->getVersion());
				_server->sendReply(_client, msg);
				msg = RPL_CREATED(_server->getServerName(), _client->getNickName());
				_server->sendReply(_client, msg);
				msg = RPL_MYINFO(_server->getServerName(), _client->getNickName(), _server->getVersion(), "User modes: ov", "Channel modes: imtlk");
				_server->sendReply(_client, msg);				
			}
			else
			{
				std::cout << "🛑 Disconnect, connection registration failed" << std::endl;
				_server->remove_fds(_client->fd);
				_server->removeClient(_client);
				_client = NULL;
			}			
	}
}