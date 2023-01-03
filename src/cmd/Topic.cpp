/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Topic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 07:34:42 by aaljaber          #+#    #+#             */
/*   Updated: 2023/01/03 06:20:24 by aaljaber         ###   ########.fr       */
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
		channel->members[i].user->sendReply(RPL_TOPIC(_server->getServerName(), _client->getNickName(), channel->getChName(), channel->getTopic()));
}

void	ft::Topic::changeTopic(void)
{
	Channel *channel = this->_server->getChannel(this->_message->getParameter()[0]);
	// ? if topic was empty it means need to clear the topic
	if (_message->getParameter()[1].empty())
	{
		std::cout << "Clear topic for channel " << channel->getChName() << std::endl;
		channel->setTopic(0);
		sendTopic();
	}
	else
	{
		std::cout << "Set this topic" << _message->getParameter()[1] << " for channel " << channel->getChName() << std::endl;
		channel->setTopic(_message->getParameter()[1]);
		sendTopic();
	}
}

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
			std::cout << BRED << "ErrMsg: need more params" << DEFCOLO << std::endl;
			_client->sendReply(ERR_NEEDMOREPARAMS(_server->getServerName(), _client->getNickName(), _message->getCommand()));
			return;
		}
		Channel *channel = this->_server->getChannel(this->_message->getParameter()[0]);
		if (!channel)
		{
			std::cout << BRED << "ErrMsg: no such a channel" << DEFCOLO << std::endl;
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
						std::cout << BRED << "ErrMsg: not a channel operator" << DEFCOLO << std::endl;
						_client->sendReply(ERR_CHANOPRIVSNEEDED(_server->getServerName(), _client->getNickName())); // ! ErrMsg need operator PRIVELEGE
					}
				}
				else
					changeTopic(); // ? the mode is not set .. anyone can change the topic
			}
			else
			{
				std::cout << BRED << "ErrMsg: User not on channel" << DEFCOLO << std::endl;
				_client->sendReply(ERR_NOTONCHANNEL(_server->getServerName(), _client->getNickName(), channel->getChName())); // ! ErrMsg not in channel
			}
		}
		else
		{
			std::cout << "Send topic to User" << std::endl;
			// ? send the topic
			if (channel->getTopic().empty())
				_client->sendReply(RPL_NOTOPIC(_server->getServerName(), _client->getNickName(), channel->getChName()));
			else
				_client->sendReply(RPL_TOPIC(_server->getServerName(), _client->getNickName(), channel->getChName(), channel->getTopic()));
		}
	}
}