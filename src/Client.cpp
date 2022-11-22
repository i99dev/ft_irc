/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oal-tena <oal-tena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 19:47:17 by aaljaber          #+#    #+#             */
/*   Updated: 2022/11/22 06:21:05 by oal-tena         ###   ########.fr       */
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

std::string ft::Client::getChannelsJoined(void) const
{
	return (this->_channelsJoined);
}

void ft::Client::setChannelsJoined(std::string channelsJoined)
{
	this->_channelsJoined = channelsJoined;
}


std::string ft::Client::getIp(void) const
{
	return (this->_client_ip);
}

std::vector<ft::Message> ft::Client::getMsgSend(void) const
{
	char buf[1024];
	read(this->fd, buf, strlen(buf));
	std::cout << "test:" << buf << std::endl;
	return (this->_msgSend);
}

std::vector<ft::Message> ft::Client::getMsgRecv(void) const
{
	return (this->_msgRecv);
}

ft::Client::Client(int &fd, std::string servername, std::string clinet_ip)
{
	this->fd = fd;
	this->_is_authenticated = false;
	this->_is_ope = false;
	this->_attempts = 0;
	this->_client_ip = clinet_ip;
	std::cout << "New client connected from " << this->_client_ip << std::endl;
	
}

ft::Client::~Client() {}