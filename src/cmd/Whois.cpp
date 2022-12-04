/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Whois.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isaad <isaad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 06:55:45 by oal-tena          #+#    #+#             */
/*   Updated: 2022/12/05 01:53:34 by isaad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/cmd/Whois.hpp"

ft::Whois::Whois()
{
	_name = "Whois";
	_description = "Get information about a user";
	_usage = "/whois <nickname>";
}

void ft::Whois::execute()
{
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
	_client->sendReply(":" + target->getServerName() + " 311 " + target->getNickName() + " " + _message->getParameter()[0] + " " + target->getUserName() + " " + target->getHostName() + " * :" + target->getRealName());
	_client->sendReply(":" + target->getServerName() + " 378 " + target->getNickName() + " * :" + "is connecting from " + target->getNickName() + "@" + target->getIp() + " " + target->getIp());
	_client->sendReply(":" + target->getServerName() + " 312 " + target->getNickName() + " " + target->getNickName() + " " + target->getServerName() + " :" + target->getServerName() + " IRC Server");
	_client->sendReply(":" + target->getServerName() + " 379 " + target->getNickName() + " * :" + "is using modes " + target->getUSMode());
	_client->sendReply(":" + target->getServerName() + " 671 " + target->getNickName() + " " + target->getNickName() + " :" + "is not using a secure connection");
	_client->sendReply(":" + target->getServerName() + " 318 " + target->getNickName() + " " + target->getNickName() + " :");
}