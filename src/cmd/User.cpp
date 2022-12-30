/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isaad <isaad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 19:18:38 by oal-tena          #+#    #+#             */
/*   Updated: 2022/12/30 23:09:49 by isaad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/cmd/User.hpp"

ft::User::User()
{
    _name = "User";
    _description = "Set username";
    _usage = "/user <username>";
}

void ft::User::execute()
{
	if (_client)
	{
		if (_message->getParameter().size() != 4)
		{
			_client->sendReply(ERR_NEEDMOREPARAMS(_server->getServerName(), _client->getNickName(), _message->getCommand()));
			return;
		}
			_client->setUserName(_message->getParameter()[0]);
			_client->setHostName(_message->getParameter()[1]);
			_client->setServerName(_message->getParameter()[2]);
			_client->setRealName(_message->getParameter()[3]);
			std::cout << "User executed" << std::endl;
			for (long unsigned int i = 0; i < this->_message->getParameter().size(); i++)
				std::cout << i << " " << this->_message->getParameter()[i] << std::endl; 
			// std::string msg = \
			// RPL_WELCOME(_message->getParameter()[2], _message->getParameter()[0]) + \
			// RPL_YOURHOST("42_irc", _message->getParameter()[0], "0.1") + \
			// RPL_CREATED("42_irc", _message->getParameter()[0]) + \
			// RPL_MYINFO("42_irc", _message->getParameter()[0], "0.1", "iow", "ov");
			// _server->sendReply(_client, msg);
	}
}