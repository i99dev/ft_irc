/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 22:48:50 by aaljaber          #+#    #+#             */
/*   Updated: 2022/11/24 22:50:46 by aaljaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/Channel.hpp"

ft::Channel::Channel(Client *user, std::string &name)
{
	if (!this->_ChName_parse(name))
		throw WrongChannelNameRequir();
	else
		this->_name = name;
	this->_creator = user;
	_created_at = time(0);
	this->_topic = "";
	//it depends on how mant clients we can handle
	this->_max_clients = 255;
}

void	ft::Channel::addClient(Client *user)
{
	this->users.push_back(user);
}

std::string	ft::Channel::getChName(void)
{
	return (this->_name);
}

/*
! be carefull about this null condition (Protection may needed)
		// if (message->getCommand() == "PRIVMSG" && message->getParameter() == "#lala")
		// {
		// 	send(fds[i].fd, ":sasori!sasori@127.0.0.1 PRIVMSG #lala :boo\r\n",168, 0);
		// 	printf("here\n");
		// }
*/
ft::Client	*ft::Channel::getSenderinfo(int ownerFD)
{
	for (int i = -1; i < this->users.size(); ++i)
	{
		if (this->users[i]->fd == ownerFD)
			return (this->users[i]);
	}
	return (NULL);
}

std::string		ft::Channel::ChnMsgFormat(Message *message)
{
	Client *sender = this->getSenderinfo(message->gerOwnerFd());
	return (":" + sender->getNickName() + "!" + sender->getUserName() + "@" + HOST + " " + message->getCommand() + " " + this->_name + " :" + message->getParameter() + CRLF);
}

void	ft::Channel::sendMsgtoChannel(Message *message)
{
	std::string	msg = this->ChnMsgFormat(message);
	for (int i = -1; i < this->users.size(); ++i)
		send(this->users[i]->fd, msg.c_str(), msg.length(), 0);
}

ft::Channel::~Channel(){}
