/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 19:47:17 by aaljaber          #+#    #+#             */
/*   Updated: 2022/11/24 06:47:30 by aaljaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/Client.hpp"
#include <string.h>


/******************* GETTERS *******************/

std::string ft::Client::getNickName(void) const
{
	return (this->_nickName);
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

std::string ft::Client::getIp(void) const
{
	return (this->_client_ip);
}

//user messages
std::vector <ft::Message> ft::Client::getMsgSend(void) const
{
	return (this->_msgSend);
}

void ft::Client::setMsgSend(Message  msgSend)
{
	this->_msgSend.push_back(msgSend);
}

std::vector <ft::Message> ft::Client::getMsgRecv(void) const
{
	return (this->_msgRecv);
}

void ft::Client::setMsgRecv(Message  msgRecv)
{
	this->_msgRecv.push_back(msgRecv);
}

ft::Client::Client(int &fd, std::string servername, std::string clinet_ip)
{
	this->fd = fd;
	this->_is_authenticated = false;
	this->_is_ope = false;
	this->_attempts = 0;
	this->_client_ip = clinet_ip;
	std::cout << "New client connected from " << this->_client_ip << std::endl;
	std::string msg = RPL_WELCOME(servername, this->_client_ip);
	send(this->fd, msg.c_str(), msg.length(), 0);
}

ft::Client::~Client() {}