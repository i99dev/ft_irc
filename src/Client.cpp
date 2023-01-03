/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 19:47:17 by aaljaber          #+#    #+#             */
/*   Updated: 2023/01/02 20:36:58 by aaljaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/Client.hpp"
#include <string.h>
#include <sstream>
#include <string>


/******************* GETTERS *******************/

std::string ft::Client::getNickName(void) const
{
	// if (_nickName.empty())
	// 	return _userName;
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
}

std::string ft::Client::intToString(int number)
{
	std::stringstream ss;
	ss << number;
	return ss.str();
}

void ft::Client::sendReply(int reply)
{
	std::string replyToSend = this->intToString(reply);
	if (send(fd, replyToSend.c_str(), replyToSend.size(), 0) == -1)
	{
		std::cout << "Error sending reply" << std::endl;
	}
}

ft::Client::Client(int &fd, std::string servername, std::string clinet_ip)
{
	(void)servername;  //TODO: remove this later
	this->fd = fd;
	this->_is_authenticated = false;
	this->_is_ope = false;
	this->_ping = 0;
	this->_client_ip = clinet_ip;
	_nickName = "";
	_userName = "";
	_serverName = "";
	_realName = "";
	_hostName = "";
	PASSFlag = 0;
	USERflag = 0;
	NICKflag = 0;
	ALREADYREGISTERED = 0;
}

void ft::Client::setPing(int ping)
{
	this->_ping = ping;
}

int ft::Client::getPing(void) const
{
	return (this->_ping);
}

/******************* USER MODE *******************/

bool	ft::Client::isInvisible(void)
{
	for (long unsigned int i = 0; i < this->_mode.size(); i++)
	{
		if (this->_mode[i] == i_INVISIBLE)
			return (true);
	}
	return (false);
}

bool	ft::Client::isOperator(void)
{
	for (long unsigned int i = 0; i < this->_mode.size(); i++)
	{
		if (this->_mode[i] == o_OPERATOR_FLAG)
			return (true);
	}
	return (false);
}

void	ft::Client::setUserMode(char mode)
{
	if (ft::ModeTools::findUserMode(mode) != n_NO_MODE)
		this->_mode.push_back(ft::ModeTools::findUserMode(mode));
}

void	ft::Client::removeUserMode(char mode)
{
	for (long unsigned int i = 0; i < this->_mode.size(); i++)
	{
		if (this->_mode[i] == ft::ModeTools::findUserMode(mode))
		{
			this->_mode.erase(this->_mode.begin() + i);
			return ;
		}
	}
}

bool	ft::Client::isUSModeSet(char mode)
{
	if (ft::ModeTools::findUserMode(mode) != n_NO_MODE)
	{
		for (long unsigned int i = 0; i < this->_mode.size(); i++)
		{
			if (this->_mode[i] == ft::ModeTools::findUserMode(mode))
				return (true);
		}
	}
	return (false);
}

int ft::Client::getSocket(void) const
{
	return (this->fd);
}

void ft::Client::setSocket(int socket)
{
    this->fd = socket;
}

std::string	ft::Client::getUSMode(void)
{
	std::string mode = "";
	for (long unsigned int i = 0; i < this->_mode.size(); i++)
		mode += ft::ModeTools::getUSModechar(this->_mode[i]);
	return (mode);
}


ft::Client::~Client() {
	// clear all the messages
	_msgRecv.clear();
	_msgSend.clear();
}