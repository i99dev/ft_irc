/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Topic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 07:34:42 by aaljaber          #+#    #+#             */
/*   Updated: 2022/12/08 10:54:30 by aaljaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/cmd/Topic.hpp"

ft::Topic::Topic(void)
{
    _name =  "Nick";
    _description = "Change your nickname or set it if you don't have one";
    _usage = "/nick <nickname>";
}

/*

TODO: check if the client need to be a member to check the TOPIC

*/
void	ft::Topic::execute(void)
{
	std::cout << "execute topic commmand" << std::endl;
	for (long unsigned int i = 0; i < this->_message->getParameter().size(); i++)
	{
		if (this->_message->getParameter()[i].empty())
			std::cout << i << " empty" << std::endl;
		else std::cout << i << " " << this->_message->getParameter()[i] << std::endl;
		// for (size_t j = 0; j < this->_message->getParameter()[i].size(); j++)
		// 	std::cout << "i " << i << " j " << j << " " << (int)this->_message->getParameter()[i][j] << std::endl;
	}
	Channel *channel = this->_server->getChannel(this->_message->getParameter()[0]);
	if (this->_message->getParameter().size() > 1)
	{
		// ? change the topic
		// ? only member can change the topic
		if (channel->isMember(_client->fd))
		{
			// ? check the mode of the channel if it's allowed to users to change the topic
			if (channel->isCHModeSet('t'))
			{
				// ? check if operator to change the topic
				if (channel->isMemberOperator(_client->fd))
				{
					channel->setTopic(_message->getParameter()[1]);
					std::string topicMsg = RPL_TOPIC(_server->getServerName(), _client->getNickName(), channel->getChName(), channel->getTopic());
					_client->sendReply(topicMsg);
				}
				else
				{
					// ! ErrMsg need operator PRIVELEGE
					std::string errMsg = ERR_CHANOPRIVSNEEDED(_server->getServerName(), _client->getNickName());
					_client->sendReply(errMsg);
				}
			}
			else
			{
				// ? the mode is not set .. anyone can change the topic
				channel->setTopic(_message->getParameter()[1]);
				std::string topicMsg = RPL_TOPIC(_server->getServerName(), _client->getNickName(), channel->getChName(), channel->getTopic());
				_client->sendReply(topicMsg);
			}
		}
		else
		{
			// ! ErrMsg not in channel
			std::string errMsg = ERR_NOTONCHANNEL(_server->getServerName(), _client->getNickName(), channel->getChName());
			_client->sendReply(errMsg);
		}
	}
	else
	{
		// ? send the topic
		std::string topicMsg = RPL_TOPIC(_server->getServerName(), _client->getNickName(), channel->getChName(), channel->getTopic());
		_client->sendReply(topicMsg);
	}
}