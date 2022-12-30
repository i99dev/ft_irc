/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Who.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isaad <isaad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 06:55:45 by oal-tena          #+#    #+#             */
/*   Updated: 2022/12/30 22:04:38 by isaad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/cmd/Who.hpp"

ft::Who::Who(void)
{
	_name = "WHO";
	_usage = "WHO [<mask>[,<mask>]]";
	_description = "Get information about a user";
}

void ft::Who::execute()
{
	if (_client->getNickName() == "")
	{
		_client->sendReply("431 :No nickname given");
		return;
	}
	if (_message->getParameter().size() != 1){
		_client->sendReply(ERR_NEEDMOREPARAMS(_server->getServerName(), _client->getNickName(), _message->getCommand()));
		return;
	}
	ft::Client *target;
	int flag = 0;
	for (int i = 0; i < int(_server->clients.size()); i++){
		if (_server->clients[i]->getNickName() == _message->getParameter()[0]){
			flag = 1;
			target = _server->clients[i];
		}
	}
	if (flag == 0){
		_client->sendReply(ERR_NOSUCHNICK(_server->getServerName(), _message->getParameter()[0]));
		return ;
	}
	// // <channel> <user name> <hostname> <server> <nick> <status> :<hops> <realname>
	// // ":" + target->getServerName() + " 318 " + target->getNickName() + " "
	// _client->sendReply(":" + target->getServerName() + " 352 " + target->getNickName() + " " + "channel" + " " + target->getUserName() + " " + target->getHostName() + " " + target->getServerName() + target->getNickName() + " " + "offline" + " :" + "hops" + " " + target->getRealName() + "\n" +
	// ":" + target->getServerName() + " 315 " + target->getNickName() + " :" + "End of /WHO list.");
	std::string reply = "";
	reply += target->getNickName() + " " +
			 target->getUserName() + " " +
			 target->getHostName() + " " +
			 "*" + " " +
			 target->getRealName();
			 //":" + serverName + " 352 " + clientNick + " * " + reply
	// _client->sendReply(":" + target->getServerName() + " 352 " + target->getNickName() + reply + "\n" +
	// ":" + target->getServerName() + " 315 " + target->getNickName() + " :" + "End of /WHO list.");
	// _client->sendReply(RPL_ENDOFWHO(_server->getServerName(), _client->getNickName(), _message->getParameter()[0]));
	std::cout << "WHO executed" << std::endl;
}