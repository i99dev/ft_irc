/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 22:48:50 by aaljaber          #+#    #+#             */
/*   Updated: 2022/12/08 17:17:51 by aaljaber         ###   ########.fr       */
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
	this->_limit = 0;
	this->_topic = "";
	std::cout << "created channel:" << _name << std::endl;
}

ft::Channel::~Channel(){}

// * Channel Check * //

bool	ft::Channel::isMember(int ownerFD)
{
	for (long unsigned int i = 0; i < this->members.size(); i++)
	{
		if (this->members[i].user->fd == ownerFD)
			return (true);
	}
	return (false);
}

bool	ft::Channel::isMember(std::string nick)
{
	for (long unsigned int i = 0; i < this->members.size(); i++)
	{
		if (this->members[i].user->getNickName() == nick)
			return (true);
	}
	return (false);
}

bool	ft::Channel::isMemberOperator(int OwnerFd)
{
	for (long unsigned int i = 0; i < this->members.size(); i++)
	{
		if (this->members[i].user->fd == OwnerFd)
		{
			if (this->members[i].user_mode == o_OPERATOR_PRIVILEGE || this->members[i].user_mode == O_CHANNEL_CREATOR)
				return (true);
		}
	}
	return (false);
}

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

ft::Client		*ft::Channel::getMember(std::string nick)
{
	for (long unsigned int i = 0; i < this->members.size(); i++)
	{
		if (this->members[i].user->getNickName() == nick)
			return (this->members[i].user);
	}
	// ! if not a member
	return (NULL);	
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
int	ft::Channel::setChannelMode(char mode, std::string param)
{
	if (ft::ModeTools::isCHMode(mode))
		this->_mode.push_back(ft::ModeTools::findChannelMode(mode));
	if (mode == 'k')
		setPassword(param);
	else if (mode == 'l')
		this->_limit = atoi(param.c_str());
	else if (mode == 'o')
		return (this->setMemberMode(this->getMember(param), 'o'));
	else if (mode == 'v')
		return (this->setMemberMode(this->getMember(param), 'v'));
	return (1);
}

int	ft::Channel::removeChannelMode(char mode, std::string param)
{
	for (long unsigned int i = 0; i < this->_mode.size(); i++)
	{
		if (this->_mode[i] == ft::ModeTools::findChannelMode(mode))
		{
			this->_mode.erase(this->_mode.begin() + i);
			if (mode == 'k')
				_password = "";
			else if (mode == 'l')
				this->_limit = 0;
			else if (mode == 'o')
				return (this->removeMemberMode(this->getMember(param), 'o'));
			else if (mode == 'v')
				return (this->removeMemberMode(this->getMember(param), 'v'));
			return (1);
		}
	}
	return (0);
}

//! check if the user was already in channel
//! remove mode check for (- and +)
int	ft::Channel::setMemberMode(Client *user, char mode)
{
	if (user == NULL)
		return (0);
	if (ft::ModeTools::findChannelMode(mode) != NO_MODE)
	{
		for (long unsigned int i = 0; i < this->members.size(); i++)
		{
			if (this->members[i].user->fd == user->fd)
			{
				this->members[i].user_mode = ft::ModeTools::findChannelMode(mode);
				return (1);
			}
		}
	}
	return (0);
}

int	ft::Channel::removeMemberMode(Client *user, char mode)
{
	if (user == NULL)
		return (0);
	if (ft::ModeTools::findChannelMode(mode) != NO_MODE)
	{
		for (long unsigned int i = 0; i < this->members.size(); i++)
		{
			if (this->members[i].user->fd == user->fd)
			{
				this->members[i].user_mode = CLEAR_MODE;
				return (1);
			}
		}
	}
	return (0);
}

void	ft::Channel::setPassword(std::string &password)
{
	this->_password = password;
}

void	ft::Channel::setTopic(std::string &topic)
{
	this->_topic = topic;
}

void	ft::Channel::setTopic(int num)
{
	if (num == 0)
		this->_topic = "";
}

bool	ft::Channel::isCHModeSet(char mode)
{
	if (ft::ModeTools::findChannelMode(mode) != NO_MODE)
	{
		for (long unsigned int i = 0; i < this->_mode.size(); i++)
		{
			if (this->_mode[i] == ft::ModeTools::findChannelMode(mode))
				return (true);
		}
	}
	return (false);
}

bool	ft::Channel::isMEModeSet(Client *user, char mode)
{
	if (user == NULL)
		return (false);
	if (ft::ModeTools::findChannelMode(mode) != NO_MODE)
	{
		for (long unsigned int i = 0; i < this->members.size(); i++)
		{
			if (this->members[i].user->fd == user->fd)
			{
				if (this->members[i].user_mode == ft::ModeTools::findChannelMode(mode))
					return (true);
			}
		}
	}
	return (false);
}

// ? PART
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

std::vector<ft::Client *>	ft::Channel::getUsers(void)
{
	std::vector<ft::Client *>	members;
	for (long unsigned int i = 0; i < this->members.size(); i++)
		members.push_back(this->members[i].user);
	return (members);
}

std::string	ft::Channel::getCHMode(void)
{
	std::string mode = "";
	for (long unsigned int i = 0; i < this->_mode.size(); i++)
		mode += ft::ModeTools::getCHModechar(this->_mode[i]);
	return (mode);
}
