/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 22:48:50 by aaljaber          #+#    #+#             */
/*   Updated: 2022/12/26 17:01:57 by aaljaber         ###   ########.fr       */
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
	this->_totalMem = 1;
	this->_topic = "";
	std::cout << "created channel:" << _name << std::endl;
}

ft::Channel::~Channel()
{
	if (!_bannedList.empty())
	{
		std::cout << "free _bannedList" << std::endl;
		for (long unsigned int i = 0; i < _bannedList.size(); i++)
			delete _bannedList[i];
	}
	if (!_invitedList.empty())
	{
		std::cout << "free _invitedList" << std::endl;
		for (long unsigned int i = 0; i < _invitedList.size(); i++)
			delete _invitedList[i];
	}
	if (!_exceptedList.empty())
	{
		std::cout << "free _exceptedList" << std::endl;
		for (long unsigned int i = 0; i < _exceptedList.size(); i++)
			delete _exceptedList[i];	
	}
}

// * Channel Check * //

bool	ft::Channel::isMember(std::string nick)
{
	for (long unsigned int i = 0; i < this->members.size(); i++)
	{
		if (this->members[i].user->getNickName() == nick)
			return (true);
	}
	return (false);
}

bool	ft::Channel::isMemberOperator(std::string nick)
{
	for (long unsigned int i = 0; i < this->members.size(); i++)
	{
		if (this->members[i].user->getNickName() == nick)
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

std::string	ft::Channel::getkey(void)
{
	return (this->_key);
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

std::vector<ft::Mask *>		ft::Channel::getExceptionList(void)
{
	return (_exceptedList);
}

std::vector<ft::Mask *>		ft::Channel::getInvitedList(void)
{
	return (_invitedList);
}

std::vector<ft::Mask *>		ft::Channel::getBannedList(void)
{
	return(_bannedList);
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

bool	ft::Channel::isChannelFull()
{
	if (isCHModeSet('l') && _totalMem >= _limit)
		return (true);
	return (false);
}

bool	ft::Channel::isCorrectKey(std::string &key)
{
	if (key == _key)
		return (true);
	return (false);
}

void	ft::Channel::_addMembertoChannel(Client *user)
{
	for (long unsigned int i = 0; i < this->members.size(); i++)
	{
		// TODO: Check later 
		if (this->members[i].user->getNickName() == user->getNickName())
			return ;
	}
	ft::Channel_Member new_member;
	new_member.user = user;
	new_member.user_mode = CLEAR_MODE;
	//push 
	this->members.push_back(new_member);
}

void	ft::Channel::addUser(Client *user)
{
	if (isCHModeSet('l'))
	{
		if (_totalMem < _limit)
		{
			_totalMem++;
			std::cout << user->getNickName() << " has been added to channel" <<std::endl;
		}
		else
		{
			std::cout << "Can't add " << user->getNickName() << " .. due to the limit" <<std::endl;
			return ;
		}
	}
	_addMembertoChannel(user);
}

// ? MODE
//! check for duplicated mode, modes that can't be both set, 
//! remove mode check for (- and +)
int	ft::Channel::setChannelMode(char mode, std::string param)
{
	if (ft::ModeTools::isCHMode(mode))
	{
		std::cout << mode << " yes add the channel mode" << std::endl;
		this->_mode.push_back(ft::ModeTools::findChannelMode(mode));
	}
	if (mode == 'k')
		setKey(param);
	else if (mode == 'l')
	{
		for (size_t i = 0; i < param.size(); i++)
		{
			if (!std::isdigit(param[i]))
			{
				this->_mode.pop_back();
				return (1);
			}
		}
		this->_limit = atoi(param.c_str());
	}
	else if (mode == 'o')
		return (this->setMemberMode(this->getMember(param), 'o'));
	else if (mode == 'v')
		return (this->setMemberMode(this->getMember(param), 'v'));
	else if (ft::ModeTools::isCHflag(mode))
		return(setChannelFlag(mode, param));
	return (1);
}

int	ft::Channel::removeChannelMode(char mode, std::string param)
{
	if (ft::ModeTools::isCHMode(mode))
	{
		for (long unsigned int i = 0; i < this->_mode.size(); i++)
		{
			if (this->_mode[i] == ft::ModeTools::findChannelMode(mode))
			{
				this->_mode.erase(this->_mode.begin() + i);
				if (mode == 'k')
					_key = "";
				else if (mode == 'l')
					this->_limit = 0;
				else if (mode == 'i' && !_invitedList.empty())
					_invitedList.clear();
				return (1);
			}
		}
	}
	else if (ft::ModeTools::isMEMode(mode))
	{
		std::cout << mode << " yes it's a member mode" << std::endl;
		if (mode == 'o')
			return (this->removeMemberMode(this->getMember(param), 'o'));
		else if (mode == 'v')
			return (this->removeMemberMode(this->getMember(param), 'v'));
		return (1);
	}
	else if (ft::ModeTools::isCHflag(mode))
		return (removeChannelFlag(mode, param));
	return (0);
}

int	ft::Channel::setChannelFlag(char mode, std::string param)
{
	std::cout << "mask param " << param << std::endl;
	Mask *mask = new Mask(param);
	
	if (mask->is_mask)
	{
		std::cout << "yes it's a mask " << param << std::endl;
		if (mode == 'I' && !this->isRepeatedMask(this->getInvitedList(), mask->getMask()))
		{
			if (!this->isCHModeSet('i') && !isRepeatedMask(_invitedList, mask->getMask()))
				this->_mode.push_back(ft::ModeTools::findChannelMode('i'));
			this->_invitedList.push_back(mask);
			std::cout << "set i into channel mode if it was I and i was not set" << std::endl;
			std::cout << "add to the invited list" << std::endl;
		}
		else if (mode == 'b' && !this->isRepeatedMask(this->getBannedList(), mask->getMask()))
		{
			this->_bannedList.push_back(mask);
			std::cout << "add to the ban list" << std::endl;
		}
		else if (mode == 'e' && !this->isRepeatedMask(this->getExceptionList(), mask->getMask()))
		{
			this->_exceptedList.push_back(mask);
			std::cout << "add to the exception list" << std::endl;
		}
		else
			delete mask;
		return (1);
	}
	delete mask;
	return (1);
}

int	ft::Channel::removeChannelFlag(char mode, std::string param)
{
	Mask *mask = new Mask(param);
	if (mask->is_mask)
	{
		if (mode == 'I')
		{
			//  TODO: check if the mask was there using isrepeated function then delete it using findMask
			if (isRepeatedMask(_invitedList, mask->getMask()) && !_invitedList.empty())
			{
				std::cout << "pos " << _findMask(_invitedList, mask->getMask()) << std::endl;
				std::cout << _invitedList[0]->getMask()->nick << std::endl;
				int i = _findMask(_invitedList, mask->getMask());
				delete _invitedList[i];
				_invitedList.erase(_invitedList.begin() + i);
				std::cout << "delete " << param << " from the invite list" << std::endl;
			}
		}
		else if (mode == 'b')
		{
			if (isRepeatedMask(_bannedList, mask->getMask()) && !_bannedList.empty())
			{
				int i = _findMask(_bannedList, mask->getMask());
				delete _bannedList[i];
				_bannedList.erase(_bannedList.begin() + i);
				std::cout << "delete " << param << " from the ban list" << std::endl;
			}
		}
		else if (mode == 'e')
		{
			if (isRepeatedMask(_exceptedList, mask->getMask()) && !_exceptedList.empty())
			{
				int i = _findMask(_exceptedList, mask->getMask());
				delete _exceptedList[i];
				_exceptedList.erase(_exceptedList.begin() + i);
				std::cout << "delete " << param << " from the exception list" << std::endl;
			}
		}
	}
	delete mask;
	return (1);	
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
			if (this->members[i].user->getNickName() == user->getNickName())
			{
				// ? if not an operatot not creator .. the user can be set to whatever voice priv or oper ptiv
				if (this->members[i].user_mode != O_CHANNEL_CREATOR && this->members[i].user_mode != o_OPERATOR_PRIVILEGE)
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
			if (this->members[i].user->getNickName() == user->getNickName())
			{
				this->members[i].user_mode = CLEAR_MODE;
				return (1);
			}
		}
	}
	return (0);
}

void	ft::Channel::setKey(std::string &key)
{
	this->_key = key;
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

bool	ft::Channel::isRepeatedMask(const std::vector<ft::Mask *>	&MasksList, t_mask *mask)
{
	for (long unsigned int i = 0; i < MasksList.size(); i++)
	{
		if (MasksList[i]->is_SameMask(mask))
			return (true);
	}
	return (false);
}

int	ft::Channel::_findMask(const std::vector<ft::Mask *>	&MasksList, t_mask *mask)
{
	for (long unsigned int i = 0; i < MasksList.size(); i++)
	{
		if (MasksList[i]->is_SameMask(mask))
			return (i);
	}
	return (MasksList.size());
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
			if (this->members[i].user->getNickName() == user->getNickName())
			{
				if (this->members[i].user_mode == ft::ModeTools::findChannelMode(mode))
					return (true);
			}
		}
	}
	return (false);
}

bool	ft::Channel::isUserBanned(ft::Client *client)
{
	for (long unsigned int i = 0; i < this->_bannedList.size(); i++)
	{
		if (this->_bannedList[i]->match_client_mask(client))
			return (true);
	}
	return (false);
}

bool	ft::Channel::isUserInvited(ft::Client *client)
{
	for (long unsigned int i = 0; i < this->_invitedList.size(); i++)
	{
		if (this->_invitedList[i]->match_client_mask(client))
			return (true);
	}
	return (false);
}

bool	ft::Channel::isUserExcepted(ft::Client *client)
{
	for (long unsigned int i = 0; i < this->_exceptedList.size(); i++)
	{
		if (this->_exceptedList[i]->match_client_mask(client))
			return (true);
	}
	return (false);
}

// ? PART
void	ft::Channel::removeUser(std::string nick)
{
	for (long unsigned int i = 0; i < this->members.size(); i++)
	{
		if (this->members[i].user->getNickName() == nick)
		{
			this->members.erase(this->members.begin() + i);
			return ;
		}	
	}
}

std::string	ft::Channel::getCHMode(void)
{
	std::string mode = "";
	for (long unsigned int i = 0; i < this->_mode.size(); i++)
		mode += ft::ModeTools::getCHModechar(this->_mode[i]);
	return (mode);
}
