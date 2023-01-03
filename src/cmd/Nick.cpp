/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isaad <isaad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 00:14:34 by oal-tena          #+#    #+#             */
/*   Updated: 2023/01/03 09:13:34 by isaad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/cmd/Nick.hpp"

ft::Nick::Nick(void)
{
    _name = "Nick";
    _description = "Change your nickname or set it if you don't have one";
    _usage = "/nick <nickname>";
}

void	ft::Nick::connectClientBack()
{
	_client = NULL;
	std::string msg = RPL_WELCOMEBACK(_server->getServerName(), _message->getParameter()[0]);
	send(_server->CLIENTBACKFD, msg.c_str(), msg.size(), 0);
	for (size_t i = 0; i < _server->channels.size(); i++)
	{
		if (_server->channels[i]->isMember(_message->getParameter()[0]))
		{
			for (size_t j = 0; j < _server->channels[i]->members.size(); j++)
			{
				if (_server->channels[i]->members[j].user->fd == _server->CLIENTBACKFD)
				{
					std::string joinMsg = ":" + _message->getParameter()[0] + " JOIN " + _server->channels[i]->getChName();
					_server->channels[i]->members[j].user->sendReply(joinMsg);					
				}
			}
		}
	}
}

// TODO: i have error still need some work on it
void ft::Nick::execute()
{
	if (_client)
	{
		std::cout << BBLU << "Nick executed" << DEFCOLO << std::endl;
		if (_message->getParameter().size() != 1)
		{
			_client->sendReply(ERR_NONICKNAMEGIVEN(_server->getServerName(), _client->getNickName()));
			return;
		}
		// get nick name and clean it from \r
		std::string nickName = _message->getParameter()[0];
		// check if nick name is valid
		if (_client->getNickName() == _message->getParameter()[0])
			return ;
		if (!ft::Nick::isvalid())
		{
			std::cout << "Remove the client it's using others nick" << std::endl;
			_server->remove_fds(_client->fd);
			_server->removeClient(_client);
			_client = NULL;
			return;
		}
		if (_server->CLIENTISBACK)
		{
			connectClientBack();
			return;
		}
		if (_client)
		{
			if (_client->getNickName() == "")
			{
				_client->setNickName(nickName);
				std::cout << "The first set to the Nick " << nickName << std::endl;
				_client->NICKflag++;
				_server->registerClient(_client);
				return;
			}
			std::cout << "Changing the Nick from " << _client->getNickName() << " to " << nickName << std::endl;
			_client->sendReply(":" + _client->getNickName() + " NICK :" + nickName);
			_client->setNickName(nickName);
		}
	}
}

bool	ft::Nick::isNickOwnerRegistered(std::string nick)
{
	int clientID = -1;
	for (size_t i = 0; i < _server->getClients().size(); i++)
	{
		if (_server->getClients()[i]->getNickName() == nick)
			clientID = i;
	}
	if (clientID > -1)
	{
		if (!_server->getClients()[clientID]->ALREADYREGISTERED)
		{
			_server->remove_fds(_server->getClients()[clientID]->fd);
			_server->removeClient(_server->getClients()[clientID]);
			return (false);
		}
		return (true);
	}
	return (false);
}

bool ft::Nick::isvalid()
{
    if (_message->getParameter().size() != 1)
    {
        std::string err = "461 " + _message->getCommand() + " :Not enough parameters";
        _client->sendReply(err);
        return false;
    }
    // check if nick name is valid
    if (_message->getParameter()[0].size() > 9)
    {
        std::string err = "432 " + _message->getParameter()[0] + " :Erroneus nickname";
        _client->sendReply(err);
        return false;
    }
	if (this->isNickOwnerRegistered(_message->getParameter()[0]))
	{
		// check if nick name is already taken
		if (_server->isNickNameTaken(_message->getParameter()[0],_client))
		{
			for (size_t i = 0; i < _server->getClients().size(); i++)
			{
				if (_server->getClients()[i]->getNickName() == _message->getParameter()[0])
				{
					if (_message->getParameter()[0] == _client->getNickName())
					{
						if (_server->getClients()[i]->fd == _client->fd)
							return true;
					}
				}
			}
			std::string err = "433 " + _message->getParameter()[0] + " :Nickname is already in use";
			_client->sendReply(err);
			return false;
		}
	}
    // check if nick name not contain special char
    if (_message->getParameter()[0].find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789-_[]\\`^{}|") != std::string::npos)
    {
        std::string err = "432 " + _message->getParameter()[0] + " :Erroneus nickname";
        _client->sendReply(err);
        return false;
    }
    return true;
}
