/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isaad <isaad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 06:54:54 by oal-tena          #+#    #+#             */
/*   Updated: 2022/12/30 12:37:24 by isaad            ###   ########.fr       */
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

	std::string cmd = _message->getParameter()[0];
	std::vector<std::string> chName; // to store all channel names
	std::vector<std::string> passwords; // to store all passwords

	// loop to get all the channel names one by one
	std::string s;
	split(chName, ',');

	if (_message->getParameter().size() > 1)
		split(passwords, ',');

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
			if (!passwords[i].empty())
				channelKey = passwords[i];
		// check if channel exists
		for (int i = 0; i < int(_server->channels.size()); i++)
		{
			if (_server->channels[i]->getChName() == channelName)
			{
				flag = 1;
				if (breakers(channelName, i))
					break ;
				// check if channel has a key
				if (_server->channels[i]->isCHModeSet('k'))
				{
					// check if key is correct
					if ((_message->getParameter()[1].size() > 0 && _server->channels[i]->getkey() == channelKey) || _server->channels[i]->isUserInvited(_client))
						addClient(i);
					else
						_client->sendReply(ERR_BADCHANNELKEY(_server->getServerName(), _client->getNickName(), channelName));
				}
				else
					addClient(i);
			}
		}
		if (flag == 0){
			//if channel does not exist create 
			if (createCH(channelName, channelKey))
				break ;
		}
	}
}

void ft::Join::split(std::vector<std::string> &v, char seperator){
	std::string s;
	int i = 0;
	while(_message->getParameter()[0][i] != '\0')
	{
		if(_message->getParameter()[0][i] != seperator)
		{
			s += _message->getParameter()[0][i];
		}
		else{
			v.push_back(s);
			s.clear();
		}
		i++;
 
	}
	v.push_back(s);
}

int ft::Join::createCH(std::string channelName, std::string channelKey){
	Channel *channel;
	try
	{
		channel = new Channel(_client,channelName);
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
		return 1 ;
	}
	if (channelKey != "" && channelKey != "x"){
		channel->setChannelMode('k', channelKey);
		channel->setKey(channelKey);
	}
	// channel->addUser(_client); // don't uncomment without Ibraar authroztion !!! :) 
	_server->channels.push_back(channel);			// send message to client
	std::string joinMsg = ":" + _client->getNickName() + " JOIN " + channel->getChName();
	_client->sendReply(joinMsg);
	std::string topicMsg = RPL_TOPIC(_server->getServerName(), _client->getNickName(), channel->getChName(), channel->getTopic());
	_client->sendReply(topicMsg);
	return 0;
}

int ft::Join::breakers(std::string channelName, int i){
	// check if client is already in channel
	if (_server->channels[i]->isMember(_client->getNickName())){
		_client->sendReply(ERR_USERONCHANNEL(_server->getServerName(), _client->getNickName()));
		return 1;
	}
	// check if client is banned
	if (!_server->channels[i]->isUserExcepted(_client)){
		if (_server->channels[i]->isUserBanned(_client)){
			_client->sendReply("-!- " + _client->getNickName() + ": Cannot join channel " + channelName + " (+b) - banned");
			return 1;
		}
	}
	// check if channel is full
	if (_server->channels[i]->isCHModeSet('l')){
		if (_server->channels[i]->isChannelFull()){
			_client->sendReply("-!- " + _client->getNickName() + ": Cannot join channel " + channelName + " (+l) - channel is full");
			return 1;
		}
	}
	// check if channel is invite only
	if (_server->channels[i]->isCHModeSet('i')){
		if (!_server->channels[i]->isUserInvited(_client)){
			_client->sendReply("-!- " + _client->getNickName() + ": Cannot join channel " + channelName + " (+i) - invite only");
			return 1;
		}
	}
	return 0;
}

void ft::Join::addClient(int i){
	// add client to channel
	_server->channels[i]->addUser(_client);
	// send message to all clients in that channel
	for (size_t j = 0; j < _server->channels[i]->members.size(); j++)
		_server->channels[i]->members[j].user->sendReply(_client->getNickName() + " JOIN " + _server->channels[i]->getChName());
	std::string topicMsg = RPL_NOTOPIC(_server->getServerName(), _client->getNickName(), _server->channels[i]->getChName());
	if (_server->channels[i]->getTopic() != "SET TOPIC")
		topicMsg = RPL_TOPIC(_server->getServerName(), _client->getNickName(), _server->channels[i]->getChName(), _server->channels[i]->getTopic());
	_client->sendReply(topicMsg);
}