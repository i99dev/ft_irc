/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Part.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isaad <isaad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 00:14:34 by oal-tena          #+#    #+#             */
/*   Updated: 2022/12/01 03:01:53 by isaad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/cmd/Part.hpp"
#include <cstdio>

ft::Part::Part(void)
{
	_name =  "Part";
	_description = "Leave a channel";
	_usage = "/part <channel>";
}

void    ft::Part::execute(){
	std::string cmd = _message->getParameter()[0];
	std::string msg = "";
	if (_message->getParameter()[1].size() > 1)
		std::string msg = _message->getParameter()[1];
	int j = 0;
	int size = 0;
	int start = 0;
	char *s;
	std::vector<std::string> channels;
	int count = 1;
	// loop to get number of channels to part
	for(int i = 0; i < int(cmd.size()); i++){
		if (cmd[i] == ',')
			count++;
	}
	// loop to store each channel in the vector
	for(int i = 0; i < count; i++){
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
		channels.push_back(std::string(s));
		delete [] s;
		j++;
	}
	int flag = 0;
	int flag2 = 0;


	// loop across channels to part or incase of error return a msg
	for (int i = 0; i < count; i++){
		flag = 0; // to check if channel exists or not
		flag2 = 0; // to check if user is in that channel or not
	    // get channel name from message
	    std::string channelName = channels[i];
	    // check if channel exists
	    for (int i = 0; i < int(_server->getChannels().size()); i++)
	    {
	        if (_server->getChannels()[i]->getChName() == channelName)
	        {
				flag = 1;
				// check if user is in that channel
				for (int j = 0; j < int(_server->getChannels()[i]->getUsers().size()); j++){
					if (_server->getChannels()[i]->getUsers()[j]->getNickName() == _client->getNickName()){
						flag2 = 1;
						std::string joinMsg = "";
		                // remove client from channel
						_server->getChannels()[i]->removeUser(_client->fd);
						joinMsg = ":" + _client->getNickName() + " PART :" + _server->getChannels()[i]->getChName();
						_client->sendReply(joinMsg);
		                // send message to clients in channel
						std::vector<Client *> clients = (_server->getChannels()[i])->getUsers();
						std::vector<Client *>::iterator it2 = clients.begin();
						for (; it2 != clients.end(); it2++)
						{
							if (msg == "")
								joinMsg = ":" + _client->getNickName() + " PART :" + _server->getChannels()[i]->getChName();
							else
								joinMsg = ":" + _client->getNickName() + " PART :" + _server->getChannels()[i]->getChName() + " :" + msg;
							(*it2)->sendReply(joinMsg);
						}
					}
				}
	        }
	    }
		if (flag == 0){
			_client->sendReply(ERR_NOSUCHCHANNEL(_server->getServerName(), _client->getNickName(), channelName));
		}
		if (flag2 == 0){
			_client->sendReply(ERR_NOTONCHANNEL(_server->getServerName(), _client->getNickName(), channelName));
		}
	}
}