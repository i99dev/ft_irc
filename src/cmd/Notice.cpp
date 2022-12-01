/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Notice.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isaad <isaad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 00:14:34 by oal-tena          #+#    #+#             */
/*   Updated: 2022/12/01 04:54:53 by isaad            ###   ########.fr       */
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

	for (int i = 0; i < int(_server->channels.size()); i++){
		if (_server->channels[i]->getChName() == target){
			std::vector<Client *> clients = (_server->getChannels()[i])->getUsers();
			std::vector<Client *>::iterator it2 = clients.begin();
			for (; it2 != clients.end(); it2++)
			{
				joinMsg = ":" + _client->getNickName() + " NOTICE " + msg;
				(*it2)->sendReply(joinMsg);
			}
		}
	}
	for (int i = 0; i < int(_server->clients.size()); i++){
		if (_server->clients[i]->getNickName() == target){
			joinMsg = ":" + _client->getNickName() + " NOTICE " + msg;
			_server->clients[i]->sendReply(joinMsg);
		}
	}
}