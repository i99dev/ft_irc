/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Part.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 00:14:34 by oal-tena          #+#    #+#             */
/*   Updated: 2022/12/26 14:00:31 by aaljaber         ###   ########.fr       */
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
	if (_message->getParameter().size() < 1 && _message->getParameter().size() > 2)
	{
		_client->sendReply(ERR_NEEDMOREPARAMS(_server->getServerName(), _client->getNickName(), _message->getCommand()));
		return;
	}
	std::string cmd = _message->getParameter()[0];
	std::string msg = "";
	if (_message->getParameter().size() > 1)
		msg = _message->getParameter()[1];
	std::vector<std::string> channels;
	std::string s;
	int i = 0;
	while(_message->getParameter()[0][i] != '\0')
	{
		if(_message->getParameter()[0][i] != ',')
		{
			s += _message->getParameter()[0][i];   // append the char array to the temp string
		}
		else{
			channels.push_back(s);
			s.clear();
		}
		i++;
 
	}
	channels.push_back(s);
	i = 0;
	int flag = 0;
	int flag2 = 0;


	// loop across channels to part or incase of error return a msg
	for (int i = 0; i < int(channels.size()); i++){
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
						_server->getChannels()[i]->removeUser(_client->getNickName());
						joinMsg = ":" + _client->getNickName() + " PART :" + _server->getChannels()[i]->getChName();
						_client->sendReply(joinMsg);
		                // send message to clients in channel
						std::vector<Client *> clients = (_server->getChannels()[i])->getUsers();
						std::vector<Client *>::iterator it2 = clients.begin();
						for (; it2 != clients.end(); it2++)
						{
							joinMsg = ":" + _client->getNickName() + " PART " + _server->getChannels()[i]->getChName() + " :" + msg;
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