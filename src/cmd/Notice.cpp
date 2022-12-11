/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Notice.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isaad <isaad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 00:14:34 by oal-tena          #+#    #+#             */
/*   Updated: 2022/12/08 15:12:20 by isaad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/cmd/Notice.hpp"

ft::Notice::Notice(){
	_name = "Notice";
	_description = "Send a notice to a user or channel";
	_usage = "Usage: /notice <nickname> <message>";
}

void ft::Notice::execute(){
	std::string target = _message->getParameter()[0];
	std::string msg = _message->getParameter()[1];
	std::string joinMsg = "";
	bool ok = false;
	int flag = 0;

	for (int i = 0; i < int(_server->channels.size()); i++){
		if (_server->channels[i]->getChName() == target){
			flag = 1;
			std::vector<Client *> clients = (_server->getChannels()[i])->getUsers();
			std::vector<Client *>::iterator it2 = clients.begin();
			for (; it2 != clients.end(); it2++)
			{
				if ((*it2)->getNickName() == _client->getNickName() && !ok){
					ok = true;
					it2 = clients.begin();
				}
				if (ok){
					joinMsg = ":" + _client->getNickName() + " NOTICE " + target + " :" + msg;
					(*it2)->sendReply(joinMsg);
				}
			}
		}
	}
	for (int i = 0; i < int(_server->clients.size()); i++){
		if (_server->clients[i]->getNickName() == target){
			joinMsg = ":" + _client->getNickName() + " NOTICE " + target + " :" + msg;;
			_server->clients[i]->sendReply(joinMsg);
			return ;
		}
	}
	if (flag == 0){
		_client->sendReply(ERR_NOSUCHNICK(_server->getServerName(), target));
		return ;
	}
	if (!ok){
		_client->sendReply(ERR_NOTONCHANNEL(_server->getServerName(), _client->getNickName(), _message->getParameter()[0]));
	}
}