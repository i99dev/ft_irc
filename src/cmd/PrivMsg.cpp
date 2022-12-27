/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PrivMsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 06:54:54 by oal-tena          #+#    #+#             */
/*   Updated: 2022/12/27 13:17:28 by aaljaber         ###   ########.fr       */
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
			for (size_t i = 0; i < (*it)->members.size(); i++)
			{
				flag = 1;
				if ((*it)->members[i].user->getNickName() != _client->getNickName())
				{
					std::cout << _client->getNickName() << " sending msg to " << (*it)->members[i].user->getNickName() <<  std::endl;
					std::string reply = ":" + _client->getNickName() + "!" + _client->getUserName() + "@" + _client->getIp() + " PRIVMSG " + channelName + " :" + msg;
					(*it)->members[i].user->sendReply(reply);
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
