/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 19:47:17 by aaljaber          #+#    #+#             */
/*   Updated: 2022/11/09 20:04:31 by aaljaber         ###   ########.fr       */
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

ft::Client::Client(){}

ft::Client::~Client(){}