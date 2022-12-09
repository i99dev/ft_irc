/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isaad <isaad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 06:56:51 by oal-tena          #+#    #+#             */
/*   Updated: 2022/12/09 08:53:47 by isaad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/cmd/Kick.hpp"

ft::Kick::Kick(void)
{
	_name = "Kick";
	_description = "Kicks a user from a channel. (forced part)";
	_usage = "kick <channel>{,<channel>} <user>{,<user>} [<comment>]";
}

void ft::Kick::execute(){
	if (_client->getNickName() == _message->getParameter()[1])
		return;
	int Count = 1;
	char *s;
	std::string cmd = _message->getParameter()[0];
	std::vector<std::string> chName; // to store all channel names

	int j = 0;
	int size = 0;
	int start = 0;
	// count the number of channels written in one command
	for(int i = 0; i < int(cmd.size()); i++){
		if (cmd[i] == ',')
			Count++;
	}
	// loop to get all the channel names one by one
	for(int i = 0; i < Count; i++){
		size = 0;
		if (cmd[j] != ',' && cmd[j])
			start = j;
		while(j < int(cmd.size())){
			if (cmd[j] == ',')
				break ;
			j++;
			size++;
		}
		s = new char[size + 1];
		cmd.copy(s, size, start);
		s[size] = 0;
		chName.push_back(std::string(s));
		delete [] s;
		j++;
	}
	bool ok = false;

	ft::Client *target;
	for (int i = 0; i < int(_server->clients.size()); i++){
		if (_server->clients[i]->getNickName() == _message->getParameter()[1]){
			target = _server->clients[i];
			ok = true;
		}
	}
	if (!ok){
		_client->sendReply(ERR_NOSUCHNICK(_server->getServerName(), _message->getParameter()[1]));
		return ;
	}

	for (int i = 0; i < Count; i++){
		ok = false;
		for (int j = 0; j < int(_server->channels.size()); j++){
			if (_server->channels[j]->getChName() == chName[i]){ // to check if channel exists and get the channel
				if (_server->channels[j]->isMember(_client->getNickName()) == false){ // to check if user is in channel
					_client->sendReply(ERR_NOTONCHANNEL(_server->getServerName(), _client->getNickName(), _server->channels[j]->getChName()));
					return ;
				}
				if (_server->channels[j]->isMemberOperator(_client->fd) == false){ // to check previliges
					_client->sendReply(":" + _server->getServerName() + " 481 " + _client->getNickName() + " :You need operator Privilege\n");
					return ;
				}
				ok = true;
				if (_server->channels[j]->isMember(target->getNickName()) == false){ // to check if user is in channel
					_client->sendReply(ERR_USERNOTINCHANNEL(_server->getServerName(), target->getNickName(), _server->channels[j]->getChName()));
					return ;
				}
				_server->channels[j]->removeUser(target->fd);
				target->sendReply(":" + _client->getNickName() + " KICK " + _server->channels[j]->getChName() + " " + target->getNickName() + " :" + _message->getParameter()[2]);
				std::vector<Client *> clients = (_server->channels[j])->getUsers();
				std::vector<Client *>::iterator it2 = clients.begin();
				for (; it2 != clients.end(); it2++)
				{
					(*it2)->sendReply(":" + _client->getNickName() + " KICK " + _server->channels[j]->getChName() + " " + target->getNickName() + " :" + _message->getParameter()[2]);
				}
			}
		}
		if (ok == false)
			_client->sendReply(ERR_NOSUCHCHANNEL(_server->getServerName(), _client->getNickName(), chName[i]));
	}
}