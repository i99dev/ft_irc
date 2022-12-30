/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Whois.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isaad <isaad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 06:55:45 by oal-tena          #+#    #+#             */
/*   Updated: 2022/12/30 22:04:49 by isaad            ###   ########.fr       */
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
	if (_client->getNickName() == "")
	{
		_client->sendReply("431 :No nickname given");
		return;
	}
	if (_message->getParameter().size() != 1){
		_client->sendReply(ERR_NEEDMOREPARAMS(_server->getServerName(), _client->getNickName(), _message->getCommand()));
		return;
	}
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
		for (int j = 0; j < int(_server->channels[i]->members.size()); j++){
			if (_server->channels[i]->members[j].user->getNickName() == target->getNickName()){
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
	_client->sendReply(":" + target->getServerName() + " 311 " + target->getNickName() + " " + _message->getParameter()[0] + " " + target->getUserName() + " " + target->getHostName() + " * :" + target->getRealName() + "\n" // whois user
	":" + target->getServerName() + " 378 " + target->getNickName() + " * :" + "is connecting from " + target->getNickName() + "@" + target->getIp() + " " + target->getIp() + "\n" // whois host
	+ ch + // whois channels
	":" + target->getServerName() + " 312 " + target->getNickName() + " " + target->getNickName() + " " + target->getServerName() + " :" + target->getServerName() + " IRC Server" + "\n" // whois server
	":" + target->getServerName() + " 379 " + target->getNickName() + " * :" + "is using modes " + target->getUSMode() + "\n" // whois modes
	":" + target->getServerName() + " 671 " + target->getNickName() + " " + target->getNickName() + " :" + "is not using a secure connection" + "\n" // whois secure
	":" + target->getServerName() + " 318 " + target->getNickName() + " " + target->getNickName() + " :"); // end of whois
}