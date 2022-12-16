/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isaad <isaad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 00:14:34 by oal-tena          #+#    #+#             */
/*   Updated: 2022/12/15 02:49:52 by isaad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/cmd/Nick.hpp"

ft::Nick::Nick(void)
{
    _name =  "Nick";
    _description = "Change your nickname or set it if you don't have one";
    _usage = "/nick <nickname>";
}

//TODO: i have error still need some work on it
void ft::Nick::execute()
{
    if (_message->getParameter().size() != 1)
	{
		_client->sendReply(ERR_NEEDMOREPARAMS(_server->getServerName(), _client->getNickName(), _message->getCommand()));
		return;
	}
    //get nick name and clean it from \r 
    std::string nickName =_message->getParameter()[0];
    //check if nick name is valid
    if(!ft::Nick::isvalid())
        return;
    if (_client->getNickName() == "")
    {
        _client->setNickName(nickName);
        std::string msg = RPL_WELCOME(_server->getServerName(), nickName);
        _server->sendReply(_client,msg);
        msg = RPL_YOURHOST(_server->getServerName(),_client->getNickName(), _server->getVersion());
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

bool ft::Nick::isvalid()
{
    if (_message->getParameter().size() != 1)
    {
        std::string err = "461 " + _message->getCommand() + " :Not enough parameters";
        _client->sendReply(err);
        return false;
    }
    //check if nick name is valid
    if (_message->getParameter()[0].size() > 9)
    {
        std::string err = "432 " + _message->getParameter()[0] + " :Erroneus nickname";
        _client->sendReply(err);
        return false;
    }
    //check if nick name is already taken
    if (_server->isNickNameTaken(_message->getParameter()[0]))
    {
        std::string errNickNameUse = ERR_NICKNAMEINUSE(_server->getServerName(), _message->getParameter()[0]);
        _client->sendReply(errNickNameUse);
        return false;
    }
    //check if nick name not contain special char
    if (_message->getParameter()[0].find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789-_[]\\`^{}|") != std::string::npos)
    {
        std::string err = "432 " + _message->getParameter()[0] + " :Erroneus nickname";
        _client->sendReply(err);
        return false;
    }
    return true;
}