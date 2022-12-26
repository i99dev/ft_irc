/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 06:56:51 by oal-tena          #+#    #+#             */
/*   Updated: 2022/12/26 09:26:39 by aaljaber         ###   ########.fr       */
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
		// std::cout << "here " << mode[i] << std::endl;
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
			* CHANGE CHANNEL MODE
*/
void	ft::Mode::actionToChangeCHMode(char mode, std::string param, char action)
{
	Channel *channel = this->_server->getChannel(this->_message->getParameter()[0]);
	if (action == SET)
	{
		if ((ft::ModeTools::isMEMode(mode) && !channel->isMEModeSet(channel->getMember(param), mode)) || (ft::ModeTools::isCHMode(mode) && !channel->isCHModeSet(mode)) || (ft::ModeTools::isCHflag(mode)))
		{
			std::cout << "set the channel mode" << std::endl;
			if (!channel->setChannelMode(mode, param))
			{
				std::string errmsg = ERR_USERNOTINCHANNEL(this->_server->getServerName(), param, channel->getChName());
				this->_client->sendReply(errmsg);
				std::cout << "Errmsg not a member" << std::endl;
			}
		}
	}
	else if (action == REMOVE)
	{
		if ((ft::ModeTools::isMEMode(mode) && channel->isMEModeSet(channel->getMember(param), mode)) || (ft::ModeTools::isCHMode(mode) && channel->isCHModeSet(mode)) || (ft::ModeTools::isCHflag(mode)))
		{
			std::cout << "remove the channel mode" << std::endl;
			if (!channel->removeChannelMode(mode, param))
			{
				std::string errmsg = ERR_USERNOTINCHANNEL(this->_server->getServerName(), param, channel->getChName());
				this->_client->sendReply(errmsg);
				std::cout << "Errmsg not a member" << std::endl;
			}
		}
	}
}

void	ft::Mode::changeCHMode(void)
{
	int pM_count = 0;
	std::cout << "change the channel mode" << std::endl;
	for (long unsigned int i = 0; i < this->modes[MODE].size(); i++)
	{
		// std::cout << "is channel mode " << ft::ModeTools::isCHMode(this->modes[MODE][i]) << std::endl;
		// std::cout << "is member mode " << ft::ModeTools::isMEMode(this->modes[MODE][i]) << std::endl;
		// std::cout << "is param mode " << ft::ModeTools::isParamMode(this->modes[MODE][i]) << std::endl;
		if (!ft::ModeTools::isCHMode(this->modes[MODE][i]) && !ft::ModeTools::isMEMode(this->modes[MODE][i]) && !ft::ModeTools::isCHflag(this->modes[MODE][i]))
		{
			// ! ErrMsg unknown channel mode
			std::string mode = "";
			mode += this->modes[MODE][i];
			std::string errmsg = ERR_UNKNOWNMODE(this->_server->getServerName(), this->_client->getNickName(), mode, _message->getParameter()[0]);
			this->_client->sendReply(errmsg);
			std::cout << this->modes[MODE][i] << " not a channel mode" << std::endl;
		}
		else if (ft::ModeTools::isParamMode(this->modes[MODE][i]) && (this->modes[MODE][i] != 'l' || this->modes[MODE][i] != 'k'))
		{
			/*
				? this meant for modes that need param like (o, v, k, l)
				? if there were more than one param mode in required pM_count will increment
				? so that it can point at the next position for the paramter
			*/
			// ! this meant to protect accesseing the array + check if the param of the next mode is available
			std::cout << "size of mode param " << this->_message->getParameter().size() << std::endl;
			if ((size_t)(MODEPARAMPOS + pM_count) >= this->_message->getParameter().size())
			{ 
				// ! ErrMsg more param needed for mode
				std::string errmsg = ERR_NEEDMOREPARAMS(this->_server->getServerName(), this->_client->getNickName(), this->_message->getCommand());
				this->_client->sendReply(errmsg);
				std::cout << this->modes[MODE][i] << " errmsg NMP " << i << std::endl;
				continue ;
			}
			// std::cout << "get mode param " << i << std::endl;
			std::string param = this->_message->getParameter()[MODEPARAMPOS + pM_count];
			pM_count++;
			// std::cout << "param " << param << std::endl;
			actionToChangeCHMode(this->modes[MODE][i], param, this->modes[ACTION][i]);
			std::cout << this->modes[MODE][i] << " a param CHMode" << std::endl;
		}
		else
		{
			actionToChangeCHMode(this->modes[MODE][i], "", this->modes[ACTION][i]);
			std::cout << this->modes[MODE][i] << " not a param CHMode" << std::endl;
		}
	}
}

/*
? irssi doesn't support the channel mode query
? it keeps adding the + before the mode
ex. /mode #lala O -> MODE #lala +O

*/
void	ft::Mode::checkCHModeCases(ft::Channel *channel)
{
	// ! check if the client is channel operator
	if (channel->isMemberOperator(this->_client->getNickName()))
		changeCHMode();
	else
	{
		std::string	errmsg = ERR_CHANOPRIVSNEEDED(this->_server->getServerName(), this->_client->getNickName());
		this->_client->sendReply(errmsg);
		std::cout << "not a channel operator\n";
	}
}

void	ft::Mode::ChannelMode(void)
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
			// ! asking to change the mode or query about the mode
			this->initModes(this->_message->getParameter()[1]);
			std::cout << "action " << modes[0] << std::endl;
			std::cout << "mode " << modes[1] << std::endl;
			this->checkCHModeCases(channel);
			std::cout << "the channel mode now is " << channel->getCHMode() << std::endl;
		}
	}
	else
	{
		// ! send err channel doesn't exist
		std::string errMsg = ERR_NOSUCHCHANNEL(_server->getServerName(), _client->getNickName(), this->_message->getParameter()[0]);
		this->_client->sendReply(errMsg);
		std::cout << "no channel" << std::endl;
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
			std::string errmsg = ERR_UMODEUNKNOWNFLAG(this->_server->getServerName(), this->_client->getNickName(), mode);
			this->_client->sendReply(errmsg);
		}
	}
}
/*
	? irssi does that check for the parameter already
	// if (this->_message->getParameter().size() < 1)
	// {
	// 	// ! send need more params
	// 	std::cout << "more params\n";
	// 	std::string errMsg = ERR_NEEDMOREPARAMS(this->_server->getServerName(), this->_client->getNickName(), this->_message->getCommand());
	// 	this->_client->sendReply(errMsg);
	// }
*/
void	ft::Mode::UserMode(void)
{
	if (_message->getParameter().size() != 2)
	{
		_client->sendReply(ERR_NEEDMOREPARAMS(_server->getServerName(), _client->getNickName(), _message->getCommand()));
		return;
	}
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

