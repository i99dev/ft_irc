/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oal-tena <oal-tena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 00:14:34 by oal-tena          #+#    #+#             */
/*   Updated: 2022/12/20 00:37:07 by oal-tena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/cmd/Nick.hpp"

ft::Nick::Nick(void)
{
    _name = "Nick";
    _description = "Change your nickname or set it if you don't have one";
    _usage = "/nick <nickname>";
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
        //close socket
        close(_client->getSocket());
        return;
     }
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
    if (_server->isNickNameTaken(_message->getParameter()[0]))
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

// check if user have nickname connected to server or not bu send and wait for reply
// void ft::Nick::isNickNameAvailable(std::string nickname)
// {
//     size_t i;
//     for (i = 0; i < _server->clients.size(); i++)
//     {
//         std::cout << "nickname: " << nickname << std::endl;
//         if (_server->getClients()[i]->getNickName() == nickname)
//         {
//             std::cout << "send ping to socket: " << _server->getClients()[i]->getSocket() << std::endl;
//             std::string ping = "PING " + nickname + "\r";
//             send(_server->getClients()[i]->getSocket(), ping.c_str(), ping.size(), 0);
//             // wait for recv pong
//             int bytes = 0;
//             char buffer[1024];
//             bytes = recv(_server->getClients()[i]->getSocket(), buffer, 1024, 0);
//             std::cout << "===================================" << std::endl;
//             std::cout << "recv bytes: " << bytes << std::endl;
//             std::cout << "===================================" << std::endl;
//             if (bytes <= 0)
//             {
//                 struct timeval tv;
//                 tv.tv_sec = 5;
//                 tv.tv_usec = 0;
//                 setsockopt(_server->getClients()[i]->getSocket(), SOL_SOCKET, SO_RCVTIMEO, (const char *)&tv, sizeof tv);
//             }
            

//         }

//     }
// }