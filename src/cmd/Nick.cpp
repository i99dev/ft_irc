/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oal-tena <oal-tena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 00:14:34 by oal-tena          #+#    #+#             */
/*   Updated: 2022/11/29 14:49:38 by oal-tena         ###   ########.fr       */
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
    //print client count on server
    std::cout << "Client count: " << _server->getClients().size() << std::endl;
    for (std::vector<ft::Client*>::iterator it = _server->getClients().begin(); it != _server->getClients().end(); it++)
    {
        std::cout << "Client: " << (*it)->getNickName() << std::endl;
        if ((*it)->getNickName() == nickName)
        {
            std::string msg = ERR_NICKNAMEINUSE(_server->getServerName(), nickName);
            _server->sendReply(_client, msg);
            return;
        }
    }
    if (_client->getNickName() == "")
    {
        _client->setNickName(nickName);
        std::string msg = RPL_WELCOME(_server->getServerName(), nickName);
        _server->sendReply(_client, msg);
        msg = RPL_YOURHOST(_server->getServerName(),_client->getNickName(), "_server->getVersion()");
        _server->sendReply(_client, msg);
        msg = RPL_CREATED(_server->getServerName(), _client->getNickName());
        _server->sendReply(_client, msg);
        msg = RPL_MYINFO(_server->getServerName(), "_server->getVersion()", "iow", "o", "ov");
        _server->sendReply(_client, msg);
        return;
    }
    _client->setNickName(nickName);
    // std::string msg = RPL_NICKNAME(_server->getServerName(), _client->getNickName());
    
    std::cout << "Nick executed" << std::endl;
    _client->setNickName(nickName);
    //cout 
}
