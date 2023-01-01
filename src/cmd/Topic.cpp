/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Topic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 07:34:42 by aaljaber          #+#    #+#             */
/*   Updated: 2023/01/01 20:30:49 by aaljaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/cmd/Topic.hpp"

ft::Topic::Topic(void)
{
    _name =  "Topic";
    _description = "Change the topic or clear it";
    _usage = "/topic <newTopic>";
}

void	ft::Topic::sendTopic()
{
	Channel *channel = this->_server->getChannel(this->_message->getParameter()[0]);
	for (long unsigned int i = 0; i < channel->members.size(); i++)
	{
		std::cout << "the is topic" << std::endl;
		channel->members[i].user->sendReply(RPL_TOPIC(_server->getServerName(), _client->getNickName(), channel->getChName(), channel->getTopic()));
	}
}

void	ft::Topic::changeTopic(void)
{
	Channel *channel = this->_server->getChannel(this->_message->getParameter()[0]);
	// ? if topic was empty it means need to clear the topic
	if (_message->getParameter()[1].empty())
	{
		std::cout << "clear topic" << std::endl;
		channel->setTopic(0);
		sendTopic();
	}
	else
	{
		channel->setTopic(_message->getParameter()[1]);
		sendTopic();
	}
}

/*
TODO: check if the client need to be a member to check the TOPIC
	// for (long unsigned int i = 0; i < this->_message->getParameter().size(); i++)
	// {
	// 	if (this->_message->getParameter()[i].empty())
	// 		std::cout << i << " empty" << std::endl;
	// 	else std::cout << i << " " << this->_message->getParameter()[i] << std::endl;
	// 	// for (size_t j = 0; j < this->_message->getParameter()[i].size(); j++)
	// 	// 	std::cout << "i " << i << " j " << j << " " << (int)this->_message->getParameter()[i][j] << std::endl;
	// }
*/
void	ft::Topic::execute(void)
{
	if (_client)
	{
		std::cout << BBLU << "Topic executed" << DEFCOLO << std::endl;
		if (_client->getNickName() == "")
		{
			_client->sendReply("431 :No nickname given");
			return;
		}
		if (_message->getParameter().size() < 1 || _message->getParameter().size() > 2)
		{
			_client->sendReply(ERR_NEEDMOREPARAMS(_server->getServerName(), _client->getNickName(), _message->getCommand()));
			return;
		}
		Channel *channel = this->_server->getChannel(this->_message->getParameter()[0]);
		std::cout << "------>" << this->_message->getParameter()[0] << std::endl;
		if (!channel)
		{
			_client->sendReply(ERR_NOSUCHCHANNEL(_server->getServerName(), _client->getNickName(), this->_message->getParameter()[0])); // ! ErrMsg no channel
			return ;
		}
		if (this->_message->getParameter().size() > 1)
		{
			// ? change the topic
			// ? only member can change the topic
			if (channel->isMember(_client->getNickName()))
			{
				// ? check the mode of the channel if it's allowed to users to change the topic
				if (channel->isCHModeSet('t'))
				{
					if (channel->isMemberOperator(_client->getNickName())) // ? check if operator to change the topic
						changeTopic();
					else
					{
						std::cout << "not a channel operator" << std::endl;
						_client->sendReply(ERR_CHANOPRIVSNEEDED(_server->getServerName(), _client->getNickName())); // ! ErrMsg need operator PRIVELEGE
					}
				}
				else
					changeTopic(); // ? the mode is not set .. anyone can change the topic
			}
			else
			{
				_client->sendReply(ERR_NOTONCHANNEL(_server->getServerName(), _client->getNickName(), channel->getChName())); // ! ErrMsg not in channel
			}
		}
		else
		{
			std::cout << "send topic" << std::endl;
			// ? send the topic
			if (channel->getTopic().empty())
				_client->sendReply(RPL_NOTOPIC(_server->getServerName(), _client->getNickName(), channel->getChName()));
			else
				_client->sendReply(RPL_TOPIC(_server->getServerName(), _client->getNickName(), channel->getChName(), channel->getTopic()));
		}
	}
}