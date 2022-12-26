/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Invite.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 06:54:54 by oal-tena          #+#    #+#             */
/*   Updated: 2022/12/26 09:26:14 by aaljaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/cmd/Invite.hpp"

ft::Invite::Invite()
{
	_name = "Invite";
	_description = "Invite a user to a channel";
	_usage = "/invite <nickname> <channel>";
}

void ft::Invite::execute()
{
	if (_message->getParameter().size() != 2)
	{
		_client->sendReply(ERR_NEEDMOREPARAMS(_server->getServerName(), _client->getNickName(), _message->getCommand()));
		return;
	}
	bool ok = false;
	ft::Channel *channel;
	ft::Client *client;
	for (int i = 0; i < int(_server->channels.size()); i++){ // check if channel exist
		if (_server->channels[i]->getChName() == _message->getParameter()[1]){
			ok = true;
			channel = _server->channels[i];
		}
	}
	if (!ok){
		_client->sendReply(ERR_NOSUCHCHANNEL(_server->getServerName(), _client->getNickName(), _message->getParameter()[1]));
		return;
	}
	if (channel->isMemberOperator(_client->getNickName()) == false){ // check if user is operator
		_client->sendReply(":" + _server->getServerName() + " 481 " + _client->getNickName() + " :You need operator Privilege\n");
		return ;
	}
	ok = false;
	for (int i = 0; i < int(_server->clients.size()); i++){ // check if user exist
		if (_server->clients[i]->getNickName() == _message->getParameter()[0]){
			ok = true;
			client = _server->clients[i];
		}
	}
	if (!channel->isUserExcepted(client)){
		if (channel->isUserBanned(client)){
			_client->sendReply("-!- " + _client->getNickName() + ": Cannot join channel " + channel->getChName() + " (+b) - banned");
			return;
		}
	}
	if (!ok){
		_client->sendReply(ERR_NOSUCHNICK(_server->getServerName(), _client->getNickName()));
		return;
	}
	ok = false;
	for (int i = 0; i < int(channel->getUsers().size()); i++){ // check if user inviting is on channel
		if (channel->getUsers()[i]->getNickName() == _client->getNickName()){
			ok = true;
		}
	}
	if (!ok){
		_client->sendReply(ERR_NOTONCHANNEL(_server->getServerName(), _client->getNickName(), _message->getParameter()[1]));
		return ;
	}
	ok = true;
	for (int i = 0; i < int(channel->getUsers().size()); i++){ // check if user invited is on channel
		if (channel->getUsers()[i]->getNickName() == _message->getParameter()[0]){
			ok = false;
		}
	}
	if (!ok){
		_client->sendReply(ERR_USERONCHANNEL(_server->getServerName(), _client->getNickName()));
		return;
	}
	client->invites.push_back(channel->getChName()); // add channel to user invites
	client->sendReply(":" + _client->getNickName() + " INVITE " + client->getNickName() + " " + channel->getChName() + " " + _client->getNickName()); // send invite to user
	_client->sendReply(":" + _server->getServerName() + " 341 " + client->getNickName() + " " + _client->getNickName() + " " + channel->getChName()); // send msg to user inviting
}