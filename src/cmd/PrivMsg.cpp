/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PrivMsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isaad <isaad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 06:54:54 by oal-tena          #+#    #+#             */
/*   Updated: 2022/12/26 14:19:56 by isaad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/cmd/PrivMsg.hpp"
#include <iterator>
ft::Privmsg::Privmsg()
{
	_name = "privmsg";
	_description = "Send message to a set of users/channels";
	_usage = "privmsg <receptor|channel>{,<receptor|channel>} :<texto>";
}

void ft::Privmsg::execute()
{
	if (_message->getParameter().size() != 2)
	{
		_client->sendReply(ERR_NEEDMOREPARAMS(_server->getServerName(), _client->getNickName(), _message->getCommand()));
		return;
	}

	// channel
	int flag = 0;
	std::string channelName = _message->getParameter()[0];
	std::string msg = _message->getParameter()[1];
	std::vector<Channel *>::iterator it = _server->channels.begin();
	for (; it != _server->channels.end(); it++)
	{
		if ((*it)->getChName() == channelName)
		{
			if ((*it)->isMember(_client->getNickName()) == false)
			{
				_client->sendReply(ERR_NOTONCHANNEL(_server->getServerName(), _client->getNickName(), channelName));
				return;
			}
			if ((*it)->isCHModeSet('m'))
			{
				if (!(*it)->isMEModeSet(_client, 'v') && !(*it)->isMEModeSet(_client, 'o'))
				{
					":" + _client->getServerName() + " 404 " + _client->getNickName() + " " + channelName + " :Cannot send to channel, you're on mode V";
					return;
				}
			}
			std::vector<Client *> clients = (*it)->getUsers();
			std::vector<Client *>::iterator it2 = clients.begin();
			for (; it2 != clients.end(); it2++)
			{
				flag = 1;
				if ((*it2)->fd != _client->fd)
				{
					std::string reply = ":" + _client->getNickName() + "!" + _client->getUserName() + "@" + _client->getIp() + " PRIVMSG " + channelName + " :" + msg;
					(*it2)->sendReply(reply);
				}
			}
		}
	}
	if (flag == 1)
		return;
	// user to user
	std::vector<Client *>::iterator it3 = _server->clients.begin();
	for (; it3 != _server->clients.end(); it3++)
	{
		if ((*it3)->getNickName() == channelName)
		{
			std::string reply = ":" + _client->getNickName() + "!" + _client->getUserName() + "@" + _client->getIp() + " PRIVMSG " + channelName + " :" + msg;
			(*it3)->sendReply(reply);
		}
	}
}
