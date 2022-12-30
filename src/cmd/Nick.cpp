/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isaad <isaad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 00:14:34 by oal-tena          #+#    #+#             */
/*   Updated: 2022/12/30 23:09:36 by isaad            ###   ########.fr       */
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
	_server->CLIENTISBACK = false;
	std::string msg = RPL_WELCOMEBACK(_server->getServerName(), _message->getParameter()[0]);
	send(_server->CLIENTBACKFD, msg.c_str(), msg.size(), 0);
	// std::cout << "join back to old channels" << std::endl;
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
    if (_message->getParameter().size() != 1)
    {
        _client->sendReply(ERR_NEEDMOREPARAMS(_server->getServerName(), _client->getNickName(), _message->getCommand()));
        return;
    }
    // get nick name and clean it from \r
    std::string nickName = _message->getParameter()[0];
    // check if nick name is valid
    if (!ft::Nick::isvalid())
	{
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
			std::string msg = RPL_WELCOME(_server->getServerName(), nickName);
			_server->sendReply(_client, msg);
			msg = RPL_YOURHOST(_server->getServerName(), _client->getNickName(), _server->getVersion());
			_server->sendReply(_client, msg);
			msg = RPL_CREATED(_server->getServerName(), _client->getNickName());
			_server->sendReply(_client, msg);
			msg = RPL_MYINFO(_server->getServerName(), _server->getVersion(), "iow", "o", "ov");
			_server->sendReply(_client, msg);
			return;
		}
		_client->setNickName(nickName);
		
		std::string msg = RPL_WELCOME(_server->getServerName(), nickName);
		_server->sendReply(_client, msg);
	}
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
    // check if nick name is already taken
    if (_server->isNickNameTaken(_message->getParameter()[0],_client))
    {
        std::string err = "433 " + _message->getParameter()[0] + " :Nickname is already in use";
        // std::string err = ERR_NICKNAMEINUSE(_server->getServerName(), _client->getNickName());
        _client->sendReply(err);
        return false;
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
