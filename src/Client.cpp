/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oal-tena <oal-tena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 19:47:17 by aaljaber          #+#    #+#             */
/*   Updated: 2022/11/21 19:37:29 by oal-tena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/Client.hpp"
#include <string.h>


/******************* GETTERS *******************/

std::string ft::Client::getNickName(void) const
{
	return (this->_nickName);
}

std::string ft::Client::getUserName(void) const
{
	return (this->_userName);
}

std::string ft::Client::getChannelsJoined(void) const
{
	return (this->_channelsJoined);
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

ft::Client::Client(int &fd, std::string servername)
{
	this->fd = fd;
	this->_is_authenticated = false;
	this->_is_ope = false;
	this->_attempts = 0;
	//RPL_WELCOME
	send(this->fd, ":localhost 001 i99dev:Wlcome i99dev \n" , 1024, 0);
}

ft::Client::~Client() {}