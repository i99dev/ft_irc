/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isaad <isaad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 06:54:54 by oal-tena          #+#    #+#             */
/*   Updated: 2022/12/25 03:09:43 by isaad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/cmd/Join.hpp"

ft::Join::Join(void)
{
	_name = "Join";
	_description = "Join a channel";
	_usage = "/join <channel> [key]";
}

void ft::Join::execute()
{
	if (_message->getParameter().size() > 2 || _message->getParameter().size() < 1)
	{
		_client->sendReply(ERR_NEEDMOREPARAMS(_server->getServerName(), _client->getNickName(), _message->getCommand()));
		return;
	}
	int flag = 0;
		// get channel ;ist from server
	std::vector<Channel *> channels = _server->getChannels();

	std::string cmd = _message->getParameter()[0];
	std::vector<std::string> chName; // to store all channel names
	std::vector<std::string> passwords; // to store all passwords

	// loop to get all the channel names one by one
	std::string s;
	int i = 0;
	while(_message->getParameter()[0][i] != '\0')
	{
		if(_message->getParameter()[0][i] != ',')
		{
			s += _message->getParameter()[0][i];   // append the char array to the temp string
		}
		else{
			chName.push_back(s);
			s.clear();
		}
		i++;
 
	}
	chName.push_back(s);

	i = 0;
	s.clear();
	if (_message->getParameter().size() > 1){
		while(_message->getParameter()[1][i] != '\0')
		{
			if(_message->getParameter()[1][i] != ',')
			{
				s += _message->getParameter()[1][i];   // append the char array to the temp string
			}
			else{
				passwords.push_back(s);
				s.clear();
			}
			i++;
	 
		}
		passwords.push_back(s);
	}

	for (int i = 0; i < int(chName.size()); i++){
		if (chName[i][0] != '#' && chName[i][0] != '&'){
			_client->sendReply(":" + _server->getServerName() + " 403 " + _client->getNickName() + " " + chName[i] + " :Bad channel name\n");
			continue ;
		}
		flag = 0;
		// get channel name from message
		std::string channelName = chName[i];
		// get channel key from message
		std::string channelKey = "";
		if (_message->getParameter().size() > 1)
		{
			if (!passwords[i].empty()){
				channelKey = passwords[i];
			}
		}
		// check if channel exists
		for (int i = 0; i < int(channels.size()); i++)
		{
			if (channels[i]->getChName() == channelName)
			{
				int gg = 0;
				flag = 1;
				for (int j = 0; j < int(channels[i]->getUsers().size()); j++){
					if (channels[i]->getUsers()[j]->getNickName() == _client->getNickName()){
						_client->sendReply(ERR_USERONCHANNEL(_server->getServerName(), _client->getNickName()));
						gg = 1;
						break ;
					}
				}
				if (gg == 1){
					break ;
				}
				if (channels[i]->isCHModeSet('i')){
					if (!channels[i]->isUserInvited(_client)){
						_client->sendReply("-!- " + _client->getNickName() + ": Cannot join channel " + channelName + " (+i) - invite only");
						break ;
					}
				}
				if (!channels[i]->isUserExcepted(_client)){
					if (channels[i]->isUserBanned(_client)){
						_client->sendReply("-!- " + _client->getNickName() + ": Cannot join channel " + channelName + " (+b) - banned");
						break ;
					}
				}
				// check if channel has a key
				if (channels[i]->getkey() != "")
				{
					// check if key is correct
					if (_message->getParameter()[1].size() > 0 && channels[i]->getkey() == channelKey)
					{
						// add client to channel
						channels[i]->addUser(_client);
						// send message to all clients in that channel
						std::vector<Client *> clients = (channels[i])->getUsers();
						std::vector<Client *>::iterator it2 = clients.begin();
						for (; it2 != clients.end(); it2++)
						{
							// std::string joinMsg = ":" + _client->getNickName() + " NOTICE " + target + " :" + msg;
							std::string joinMsg = ":" + _client->getNickName() + " JOIN " + channels[i]->getChName();
							(*it2)->sendReply(joinMsg);
						}
						// _client->sendReply(joinMsg);
					}
					else
					{
						// send message to client
						std::string errMsg = ERR_BADCHANNELKEY(_server->getServerName(), _client->getNickName(), channelName);
						_client->sendReply(errMsg);
					}
				}
				else
				{
					// add client to channel
					channels[i]->addUser(_client);
					// send message to all clients in that channel
					std::vector<Client *> clients = (channels[i])->getUsers();
					std::vector<Client *>::iterator it2 = clients.begin();
					for (; it2 != clients.end(); it2++)
					{
						std::string joinMsg = ":" + _client->getNickName() + " JOIN " + channels[i]->getChName();
						(*it2)->sendReply(joinMsg);
					}
					// std::string joinMsg = ":" + _client->getNickName() + " JOIN " + (channels[i])->getChName();
					// _client->sendReply(joinMsg);
					std::string topicMsg;
					if (channels[i]->getTopic() != "SET TOPIC")
						topicMsg = RPL_TOPIC(_server->getServerName(), _client->getNickName(), channels[i]->getChName(), channels[i]->getTopic());
					else
						topicMsg = ":" + _client->getServerName() + " 331 " + _client->getNickName() + " " + _client->getNickName() + " " + channelName + " :No topic is set";
					_client->sendReply(topicMsg);
				}
			}
		}
		if (flag == 0){
			//if channel does not exist create 
			Channel *channel = new Channel(_client,channelName);
			if (channelKey != "" || channelKey != "x"){
				channel->setKey(channelKey);
			}
			// channel->addUser(_client); // don't uncomment without Ibraar authroztion !!! :) 
			_server->channels.push_back(channel);
			// send message to client
			std::string joinMsg = ":" + _client->getNickName() + " JOIN " + channel->getChName();
			_client->sendReply(joinMsg);
			std::cout << "3 channel name " << channel->getChName() << std::endl;
			std::string topicMsg = RPL_TOPIC(_server->getServerName(), _client->getNickName(), channel->getChName(), channel->getTopic());
			_client->sendReply(topicMsg);
		}
	}
}