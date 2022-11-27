/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 22:48:50 by aaljaber          #+#    #+#             */
/*   Updated: 2022/11/27 05:15:25 by aaljaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/Channel.hpp"

// * Constructor and Destructor * //
ft::Channel::Channel(Client *user, std::string &name)
{
	// ! no need to throw exception if the client will ignore
	if (!this->_ChName_parse(name))
		throw WrongChannelNameRequir();
	else
		this->_name = name;
	this->_creator = user;
	this->_created_at = time(0);
	this->_topic = "";
	this->_max_clients = 0; //? it depends on user limit mode + what the server can handle
}

ft::Channel::~Channel(){}

// * Getters * //
std::string	ft::Channel::getChName(void)
{
	return (this->_name);
}

// * Channel actions * //
// ? JOIN
bool	ft::Channel::_ChName_parse(std::string &name)
{
	if (name[0] == '&' || name[0] == '#' || name[0] == '+' || name[0] == '!')
	{
		if (name.find('&', 1) == std::string::npos && name.find('#', 1) == std::string::npos && name.find('+', 1) == std::string::npos && name.find('!', 1) == std::string::npos)
		{
			if (name.length() <= CHNAME_LENGTH)
			{
				if (name.find(' ') == std::string::npos && name.find(':') == std::string::npos && name.find(',') == std::string::npos && name.find(7) == std::string::npos)
					return (true);
			}
		}
	}
	return(false);
}

// ? JOIN
void	ft::Channel::addUser(Client *user)
{
	for (int i = -1; i < this->users.size(); ++i)
	{
		if (this->users[i]->fd == user->fd)
			return ;
	}
	this->users.push_back(user);
}

// ? MODE
//! check for duplicated mode, modes that can't be both set, 
//! remove mode check for (- and +)
void	ft::Channel::setChannelMode(char mode)
{
	for (int i = -1; i < MODE_NUM; ++i)
	{
		if (MODE_CHAR[i] == mode)
		{
			this->_mode.push_back(MODE_ENUM[i]);
			return ;
		}
	}
}

void	ft::Channel::addChannelOperators(Client *user)
{
	for (int i = -1; i < this->users.size(); ++i)
	{
		if (this->users[i]->fd == user->fd)
		{
			this->users.erase(this->users.begin() + i);
			this->operators.push_back(user);
			return ;
		}
	}
	/* 
		! need to make sure if the server will ignore
		! it or error message will be sent
	*/
}

// ? PRIVMSG
/*
! be carefull about this null condition (Protection may needed)
		// if (message->getCommand() == "PRIVMSG" && message->getParameter() == "#lala")
		// {
		// 	send(fds[i].fd, ":sasori!sasori@127.0.0.1 PRIVMSG #lala :boo\r\n",168, 0);
		// 	printf("here\n");
		// }
*/
ft::Client	*ft::Channel::_getSenderinfo(int ownerFD)
{
	for (int i = -1; i < this->users.size(); ++i)
	{
		if (this->users[i]->fd == ownerFD)
			return (this->users[i]);
	}
	return (NULL);
}

std::string		ft::Channel::sendMsgFormat(Message *message)
{
	Client *sender = this->_getSenderinfo(message->gerOwnerFd());
	// printf("")
	return (":sasori!sasori@127.0.0.1 PRIVMSG #lala :boo\r\n");
	// return (":" + sender->getNickName() + "!" + sender->getUserName() + "@" + HOST + " " + message->getCommand()[2] + " " + this->_name + " " + message->getCommand()[2] + CRLF);
}

void	ft::Channel::sendMsgtoChannel(Message *message)
{
	std::string	msg = this->sendMsgFormat(message);
	printf("here\n");
	for (int i = -1; i < this->users.size(); ++i)
		send(this->users[i]->fd, msg.c_str(), msg.length(), 0);
}


