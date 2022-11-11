/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oal-tena <oal-tena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 19:47:17 by aaljaber          #+#    #+#             */
/*   Updated: 2022/11/10 17:56:25 by oal-tena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/Client.hpp"


/******************* GETTERS *******************/

std::string				ft::Client::getNickName(void)const
{
	return (this->_nickName);
}

std::string				ft::Client::getUserName(void)const
{
	return (this->_userName);
}

std::string				ft::Client::getChannelsJoined(void)const
{
	return (this->_channelsJoined);
}

std::vector <ft::Message>	ft::Client::getMsgSend(void)const
{
	return (this->_msgSend);
}

std::vector <ft::Message>	ft::Client::getMsgRecv(void)const
{
	return (this->_msgRecv);
}

ft::Client::Client(int &fd)
{
	this->fd = fd;
	this->_is_authenticated = false;
	this->_is_ope = false;
	this->_attempts = 0;
}

ft::Client::~Client(){}