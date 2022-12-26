/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 06:54:54 by oal-tena          #+#    #+#             */
/*   Updated: 2022/12/26 06:00:14 by aaljaber         ###   ########.fr       */
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
	// std::vector<Channel *> channels = _server->getChannels();

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
		for (int i = 0; i < int(_server->getChannels().size()); i++)
		{
			if (_server->getChannels()[i]->getChName() == channelName)
			{
				int gg = 0;
				flag = 1;
				for (int j = 0; j < int(_server->getChannels()[i]->getUsers().size()); j++){
					if (_server->getChannels()[i]->getUsers()[j]->getNickName() == _client->getNickName()  && _server->getChannels()[i]->getUsers()[j]->fd == _client->fd ){
						_client->sendReply(ERR_USERONCHANNEL(_server->getServerName(), _client->getNickName()));
						gg = 1;
						break ;
					}
				}
				if (gg == 1){
					break ;
				}
				if (_server->getChannels()[i]->isCHModeSet('i')){
					if (!_server->getChannels()[i]->isUserInvited(_client)){
						_client->sendReply("-!- " + _client->getNickName() + ": Cannot join channel " + channelName + " (+i) - invite only");
						break ;
					}
				}
				if (!_server->getChannels()[i]->isUserExcepted(_client)){
					if (_server->getChannels()[i]->isUserBanned(_client)){
						_client->sendReply("-!- " + _client->getNickName() + ": Cannot join channel " + channelName + " (+b) - banned");
						break ;
					}
				}
				// check if channel has a key
				if (_server->getChannels()[i]->getkey() != "")
				{
					// check if key is correct
					if (_message->getParameter()[1].size() > 0 && _server->getChannels()[i]->getkey() == channelKey)
					{
						// add client to channel
						_server->getChannels()[i]->addUser(_client);
						// send message to all clients in that channel
						std::vector<Client *> clients = (_server->getChannels()[i])->getUsers();
						std::vector<Client *>::iterator it2 = clients.begin();
						for (; it2 != clients.end(); it2++)
						{
							// std::string joinMsg = ":" + _client->getNickName() + " NOTICE " + target + " :" + msg;
							std::string joinMsg = ":" + _client->getNickName() + " JOIN " + _server->getChannels()[i]->getChName();
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
					_server->getChannels()[i]->addUser(_client);
					// send message to all clients in that channel
					std::vector<Client *> clients = (_server->getChannels()[i])->getUsers();
					std::vector<Client *>::iterator it2 = clients.begin();
					for (; it2 != clients.end(); it2++)
					{
						std::string joinMsg = ":" + _client->getNickName() + " JOIN " + _server->getChannels()[i]->getChName();
						(*it2)->sendReply(joinMsg);
					}
					// std::string joinMsg = ":" + _client->getNickName() + " JOIN " + (_server->getChannels()[i])->getChName();
					// _client->sendReply(joinMsg);
					std::string topicMsg;
					if (_server->getChannels()[i]->getTopic() != "SET TOPIC")
						topicMsg = RPL_TOPIC(_server->getServerName(), _client->getNickName(), _server->getChannels()[i]->getChName(), _server->getChannels()[i]->getTopic());
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
			_server->getChannels().push_back(channel);
			std::cout << "channel vector size " << _server->getChannels().size() << std::endl;
			// send message to client
			std::string joinMsg = ":" + _client->getNickName() + " JOIN " + channel->getChName();
			_client->sendReply(joinMsg);
			std::cout << "3 channel name " << channel->getChName() << std::endl;
			std::string topicMsg = RPL_TOPIC(_server->getServerName(), _client->getNickName(), channel->getChName(), channel->getTopic());
			_client->sendReply(topicMsg);
		}
	}
}