/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 06:56:51 by oal-tena          #+#    #+#             */
/*   Updated: 2022/12/05 05:40:40 by aaljaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/cmd/Mode.hpp"

ft::Mode::Mode()
{
    _name = "Mode";
    _description = "Change user or channel mode";
    _usage = "/mode <channel> <mode> [<mode> ...]";
}

/*
			* MODE INITIALIZATION *
*/
int	ft::Mode::nextMode(std::string mode, int begin)
{
	char	action = mode[begin];
	size_t i = begin;

	while (++i < mode.length())
	{
		std::cout << "here " << mode[i] << std::endl;
		if (mode[i] == '-' || mode[i] == '+')
			return (i - 1);
		this->modes[0] += action;
		this->modes[1] += mode[i];
	}
	return (i);
}

void	ft::Mode::initModes(std::string mode)
{
	this->modes.push_back("");
	this->modes.push_back("");
	for (size_t i = 0; i < mode.length(); i++)
	{
		if (mode[i] == '-' || mode[i] == '+')
			i = nextMode(mode, i);
	}
}
//******************************************

/*
	do action
	{
		if (action == SET)
		{
			if (!setChannelMode(mode, param))
			Errmsg not a member
		}
		else if (action == REMOVE)
		{
			if (!removeChannelMode(mode, param))
			Errmsg not a member
		}
	}
*/

/*
			* CHANGE CHANNEL MODE
*/

void	ft::Mode::accessCHMode(int action)
{
	if (action == QUERY)
	{
		std::cout << "query about channel mode" << std::endl;
	}
	else if (action == CHANGE)
	{
		/*
		loop
		{
			if (!isCHmode(mode))
			{
				ErrMsg
			}
			pM_count = 0
			else if (ft::ModeTools::isParamMode(mode))
			{
				if (1 + pM_count > parm.size())
					ErrMsg more param needed
				param[1 + pM_count]
				pM_count++;
				do action (mode, param[1 + pM_count], action)
			}
			else
			{
				do action (mode, "", action)
			}
		}
		*/
		std::cout << "change the channel mode" << std::endl;
	}
}

void	ft::Mode::ChannelMode(void)
{
	// ? paramter check
	if (this->_message->getParameter().empty())
	{
		// ! send need more params
		std::cout << "more params\n";
		std::string errMsg = ERR_NEEDMOREPARAMS(this->_server->getServerName(), this->_client->getNickName(), this->_message->getCommand());
		this->_client->sendReply(errMsg);
	}
	else
	{
		// ? check if this channel is available
		if (this->_server->isChannel(this->_message->getParameter()[0]))
		{
			Channel *channel = this->_server->getChannel(this->_message->getParameter()[0]);
			if (this->_message->getParameter().size() == 1)
			{
				// ! send the current mode of the channel
				std::string reply = RPL_CHANNELMODEIS(this->_server->getServerName(), this->_client->getNickName(), channel->getChName(), channel->getCHMode());
				this->_client->sendReply(reply);
			}
			else
			{
				initModes(this->_message->getParameter()[1]);
				if (this->modes[ACTION].empty())
				{
					// ! check if the client is channel member
					if (channel->isMember(this->_client->fd))
						accessCHMode(QUERY);
					else
					{
						std::cout << "not a channel member\n";
					}
				}
				else
				{
					// ! check if the client is channel operator
					if (channel->isMemberOperator(this->_client->fd))
						accessCHMode(CHANGE);
					else
					{
						std::cout << "not a channel operator\n";
					}
				}
			}
		}
		else
		{
			std::cout << "no channel" << std::endl;
			// ! send err channel doesn't exist
		}
	}
}
//******************************************

/*
				* CHANGE USER MODE *
*/
void	ft::Mode::changeUSMode(void)
{
	for (size_t i = 0; i < this->modes[MODE].length(); i++)
	{
		if (ft::ModeTools::isUSMode(this->modes[MODE][i]))
		{
			if (this->modes[ACTION][i] == REMOVE)
			{
				if (this->_client->isUSModeSet(this->modes[MODE][i]))
				{
					this->_client->removeUserMode(this->modes[MODE][i]);
					// ! send the mode changed
					std::string reply = ":" + this->_server->getServerName() + " Mode " + this->_client->getNickName() + " " +  modes[ACTION][i] + modes[MODE][i] + "\n";
					this->_client->sendReply(reply);
				}
			}
			else if (this->modes[ACTION][i] == SET)
			{
				if (!this->_client->isUSModeSet(this->modes[MODE][i]))
				{
					this->_client->setUserMode(this->modes[MODE][i]);
					// ! send the mode changed
					std::string reply = ":" + this->_server->getServerName() + " Mode " + this->_client->getNickName() + " " +  modes[ACTION][i] + modes[MODE][i] + "\n";
					this->_client->sendReply(reply);
				}
			}
		}
		else
		{
			// ! send not an available mode
			std::string mode = "";
			mode += this->modes[MODE][i];
			std::string errmsg = ERR_UNKNOWNMODE(this->_server->getServerName(), this->_client->getNickName(), mode);
			this->_client->sendReply(errmsg);
		}
	}
}

void	ft::Mode::UserMode(void)
{
	// ? paramter check
	if (this->_message->getParameter().size() < 1)
	{
		// ! send need more params
		std::cout << "more params\n";
		std::string errMsg = ERR_NEEDMOREPARAMS(this->_server->getServerName(), this->_client->getNickName(), this->_message->getCommand());
		this->_client->sendReply(errMsg);
	}
	else
	{
		// ? mode command only applied on the same client
		std::cout << this->_client->getNickName() << " " << this->_message->getParameter()[0] << std::endl;
		if (this->_message->getParameter()[0] == this->_client->getNickName())
		{
			// ? if one param then it's asking about the mode
			if (this->_message->getParameter().size() < 2)
			{
				// ! send the modes to client
				std::string reply = RPL_UMODEIS(this->_server->getServerName(), this->_client->getNickName(), this->_client->getUSMode());
				this->_client->sendReply(reply);
			}
			else
			{
				// ? more than one param then it's changing the mode
				this->initModes(this->_message->getParameter()[1]);
				this->changeUSMode();
				std::cout << "action " << modes[0] << std::endl;
				std::cout << "mode " << modes[1] << std::endl;
			}
		}
		else
		{
			std::cout << "no match" << std::endl;
			// ! send err user didn't match
			std::string errMsg = ERR_USERSDONTMATCH(this->_server->getServerName(), this->_client->getNickName());
			this->_client->sendReply(errMsg);
		}
	}
}
//******************************************

void ft::Mode::execute(void)
{
    std::cout << "Mode executed" << std::endl;
	for (long unsigned int i = 0; i < this->_message->getParameter().size(); i++)
		std::cout << i << " " << this->_message->getParameter()[i] << std::endl;
	if (this->_message->getParameter()[0][0] == '#')
		ChannelMode();
	else
		UserMode();
	this->modes.clear();
}

