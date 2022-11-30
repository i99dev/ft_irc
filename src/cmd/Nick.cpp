/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oal-tena <oal-tena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 00:14:34 by oal-tena          #+#    #+#             */
/*   Updated: 2022/11/30 08:24:33 by oal-tena         ###   ########.fr       */
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
    //get nick name and clean it from \r 
    std::string nickName =_message->getParameter()[0].substr(0, _message->getParameter()[0].size() - 1);
    //check if nick name is valid
    if (nickName.size() > 9)
    {
        std::string err = "432 " + _message->getParameter()[0] + " :Erroneus nickname";
        _client->sendReply(err);
        return ;
    }
    //check if nick name is already taken
    if (_server->isNickNameTaken(nickName))
    {
        std::string errNickNameUse = ERR_NICKNAMEINUSE(_server->getServerName(), nickName);
        _client->sendReply(errNickNameUse);
        return ;
    }
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
