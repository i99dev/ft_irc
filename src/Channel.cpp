/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 22:48:50 by aaljaber          #+#    #+#             */
/*   Updated: 2022/11/30 13:40:51 by aaljaber         ###   ########.fr       */
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
	Channel_Member creator;
	creator.user = user;
	creator.user_mode = O_CHANNEL_CREATOR;
	this->members.push_back(creator);
	this->_created_at = time(0);
	this->_topic = "";
	std::cout << "created channel:" << _name << std::endl;
}

ft::Channel::~Channel(){}

// * Getters * //
std::string	ft::Channel::getChName(void)
{
	return (this->_name);
}

std::string	ft::Channel::getpassword(void)
{
	return (this->_password);
}

ft::Client	*ft::Channel::getCreator(void)
{
	for (long unsigned int i = 0; i < this->members.size(); i++)
	{
		if (this->members[i].user_mode == O_CHANNEL_CREATOR)
			return (this->members[i].user);
	}
	return (NULL);
}

std::vector<ft::Channel_Member>	ft::Channel::getMembers(void)
{
	return (this->members);
}

std::string	ft::Channel::getTopic(void)
{
	return (this->_topic);
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
	for (long unsigned int i = 0; i < this->members.size(); i++)
	{
		if (this->members[i].user->fd == user->fd)
			return ;
	}
	ft::Channel_Member new_member;
	new_member.user = user;
	new_member.user_mode = CLEAR_MODE;
	this->members.push_back(new_member);
}

// ? MODE
//! check for duplicated mode, modes that can't be both set, 
//! remove mode check for (- and +)
void	ft::Channel::setChannelMode(char mode)
{
	this->_mode.push_back(this->FindMode(mode));
}

void	ft::Channel::removeChannelMode(char mode)
{
	for (int i = -1; i < MODE_NUM; ++i)
	{
		if (this->_mode[i] == this->FindMode(mode))
		{
			this->_mode.erase(this->_mode.begin() + i);
			return ;
		}
	}
}

//! check if the user was already in channel
//! remove mode check for (- and +)
void	ft::Channel::setMemberMode(Client *user, char mode)
{
	if (this->FindMode(mode) != NO_MODE)
	{
		for (long unsigned int i = 0; i < this->members.size(); i++)
		{
			if (this->members[i].user->fd == user->fd)
			{
				this->members[i].user_mode = this->FindMode(mode);
				return ;
			}	
		}
	}
}

void	ft::Channel::removeMemberMode(Client *user, char mode)
{
	if (this->FindMode(mode) != NO_MODE)
	{
		for (long unsigned int i = 0; i < MODE_NUM; i++)
		{
			if (this->members[i].user->fd == user->fd)
			{
				this->members[i].user_mode = this->FindMode(mode);
				return ;
			}
		}
	}
}

void	ft::Channel::makeMemberOperator(Client *user)
{
	for (long unsigned int i = 0; i < this->members.size(); i++)
	{
		if (this->members[i].user->fd == user->fd)
		{
			this->members[i].user_mode = o_OPERATOR_PRIVILEGE;
			return ;
		}
	}
	/* 
		! need to make sure if the server will ignore
		! it or error message will be sent if the client wasn't in the channel
		! or already an operator 
	*/
}

void	ft::Channel::makeMemberVoice(Client *user)
{
	for (long unsigned int i = 0; i < this->members.size(); i++)
	{
		if (this->members[i].user->fd == user->fd)
		{
			this->members[i].user_mode = v_VOICE_PRIVILEGE;
			return ;
		}
	}
	/* 
		! need to make sure if the server will ignore
		! it or error message will be sent
	*/
}

void	ft::Channel::setPassword(std::string &password)
{
	this->_password = password;
}

void	ft::Channel::setTopic(std::string &topic)
{
	this->_topic = topic;
}

// mode tools
ft::Channel_Mode ft::Channel::FindMode(char mode)
{
	for (int i = -1; i < MODE_NUM; ++i)
	{
		if (MODE_CHAR[i] == mode)
			return (MODE_ENUM[i]);
	}
	return (CLEAR_MODE);
}

bool	ft::Channel::isChannelModerated(void)
{
	for (long unsigned int i = 0; i < this->_mode.size(); i++)
	{
		if (this->_mode[i] == m_MODERATED_CHANNEL)
			return (true);
	}
	return (false);
}

bool	ft::Channel::isChannelPrivate(void)
{
	for (long unsigned int i = 0; i < this->_mode.size(); i++)
	{
		if (this->_mode[i] == p_PRIVATE_CHANNEL)
			return (true);
	}
	return (false);
}

bool	ft::Channel::isChannelInvitedOnly(void)
{
	for (long unsigned int i = 0; i < this->_mode.size(); i++)
	{
		if (this->_mode[i] == i_INVITE_ONLY_CHANNEL)
			return (true);
	}
	return (false);
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
ft::Client	*ft::Channel::_getClientinfo(int ownerFD)
{
	for (long unsigned int i = 0; i < this->members.size(); i++)
	{
		if (this->members[i].user->fd == ownerFD)
			return (this->members[i].user);
	}
	// ! if not a member
	return (NULL);
}

std::string		ft::Channel::sendMsgFormat(Message *message)
{
	// (void)message;
	// Client *sender = this->_getClientinfo(message->gerOwnerFd());
	// return (":sasori!sasori@127.0.0.1 PRIVMSG #lala :boo\r\n");
	// return (":" + sender->getNickName() + "!" + sender->getUserName() + "@" + HOST + " " + message->getCommand() + " " + this->_name + " :" + message->getParameter()[1] + CRLF);
}

void	ft::Channel::sendMsgtoChannel(Message *message)
{
	std::string	msg = this->sendMsgFormat(message);
	printf("here\n");
	for (long unsigned int i = 0; i < this->members.size(); i++)
		send(this->members[i].user->fd, msg.c_str(), msg.length(), 0);
}

// // ? PART
void	ft::Channel::removeUser(int userFD)
{
	for (long unsigned int i = 0; i < this->members.size(); i++)
	{
		if (this->members[i].user->fd == userFD)
		{
			this->members.erase(this->members.begin() + i);
			return ;
		}	
	}
}
