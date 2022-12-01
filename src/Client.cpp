/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isaad <isaad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 19:47:17 by aaljaber          #+#    #+#             */
/*   Updated: 2022/12/01 20:31:19 by isaad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/Client.hpp"
#include <string.h>


/******************* GETTERS *******************/

std::string ft::Client::getNickName(void) const
{
	if (_nickName.empty())
		return _userName;
	return _nickName;
}

void ft::Client::setNickName(std::string nickName)
{
	this->_nickName = nickName;
}

std::string ft::Client::getUserName(void) const
{
	return (this->_userName);
}

void ft::Client::setUserName(std::string userName)
{
	this->_userName = userName;
}

std::string ft::Client::getServerName(void) const
{
	return (this->_serverName);
}

void ft::Client::setServerName(std::string serverName)
{
	this->_serverName = serverName;
}

std::string ft::Client::getRealName(void) const
{
	return (this->_realName);
}

void ft::Client::setRealName(std::string realName)
{
	this->_realName = realName;
}

std::string ft::Client::getHostName(void) const
{
	return (this->_hostName);
}

void ft::Client::setHostName(std::string hostName)
{
	this->_hostName = hostName;
}

std::string ft::Client::getIp(void) const
{
	return (this->_client_ip);
}

//user messages
std::vector <ft::Message *> ft::Client::getMsgSend(void) const
{
	return (this->_msgSend);
}

void ft::Client::setMsgSend(Message  *msgSend)
{
	this->_msgSend.push_back(msgSend);
}

std::vector <ft::Message *> ft::Client::getMsgRecv(void) const
{
	return (this->_msgRecv);
}

void ft::Client::setMsgRecv(Message  *msgRecv)
{
	this->_msgRecv.push_back(msgRecv);
}

void ft::Client::sendReply(std::string reply)
{
	std::string replyToSend = reply + "\n";
	if (send(fd, replyToSend.c_str(), replyToSend.size(), 0) == -1)
	{
		std::cout << "Error sending reply" << std::endl;
	}
	sleep(1);
}

ft::Client::Client(int &fd, std::string servername, std::string clinet_ip)
{
	(void)servername;  //TODO: remove this later
	this->fd = fd;
	this->_is_authenticated = false;
	this->_is_ope = false;
	this->_ping = 0;
	this->_client_ip = clinet_ip;
}

void ft::Client::setPing(int ping)
{
	this->_ping = ping;
}

int ft::Client::getPing(void) const
{
	return (this->_ping);
}

ft::Client::~Client() {}