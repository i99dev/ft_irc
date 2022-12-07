/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Whois.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isaad <isaad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 06:55:45 by oal-tena          #+#    #+#             */
/*   Updated: 2022/12/06 14:51:08 by isaad            ###   ########.fr       */
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
	std::vector <std::string> channels;
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
	for (int i = 0; i < int(_server->channels.size()); i++){
		for (int j = 0; j < int(_server->channels[i]->getUsers().size()); j++){
			if (_server->channels[i]->getUsers()[j]->getNickName() == target->getNickName()){
				channels.push_back(_server->channels[i]->getChName());
			}
		}
	}
	std::string ch = "";
	if (channels.size() > 0){
		ch = ":" + target->getServerName() + " 319 " + target->getNickName() + " * :";
		for (int i = 0; i < int(channels.size()); i++){
			ch += channels[i];
			if (i != int(channels.size()) - 1)
				ch += " ";
		}
		ch += "\n";
	}
	_client->sendReply(":" + target->getServerName() + " 311 " + target->getNickName() + " " + _message->getParameter()[0] + " " + target->getUserName() + " " + target->getHostName() + " * :" + target->getRealName() + "\n"
	":" + target->getServerName() + " 378 " + target->getNickName() + " * :" + "is connecting from " + target->getNickName() + "@" + target->getIp() + " " + target->getIp() + "\n"
	+ ch +
	":" + target->getServerName() + " 312 " + target->getNickName() + " " + target->getNickName() + " " + target->getServerName() + " :" + target->getServerName() + " IRC Server" + "\n"
	":" + target->getServerName() + " 379 " + target->getNickName() + " * :" + "is using modes " + target->getUSMode() + "\n"
	":" + target->getServerName() + " 671 " + target->getNickName() + " " + target->getNickName() + " :" + "is not using a secure connection" + "\n"
	":" + target->getServerName() + " 318 " + target->getNickName() + " " + target->getNickName() + " :");
}