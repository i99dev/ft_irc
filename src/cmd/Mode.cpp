/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 06:56:51 by oal-tena          #+#    #+#             */
/*   Updated: 2023/01/03 06:21:25 by aaljaber         ###   ########.fr       */
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
		if (mode[i] == '-' || mode[i] == '+')
			return (i - 1);
		this->modes[ACTION] += action;
		this->modes[MODE] += mode[i];
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
			std::cout << "Set the channel mode" << std::endl;
			if (!channel->setChannelMode(mode, param))
			{
				std::string errmsg = ERR_USERNOTINCHANNEL(this->_server->getServerName(), param, channel->getChName());
				this->_client->sendReply(errmsg);
				std::cout << "Errmsg: not a member" << std::endl;
			}
		}
	}
	else if (action == REMOVE)
	{
		if ((ft::ModeTools::isMEMode(mode) && channel->isMEModeSet(channel->getMember(param), mode)) || (ft::ModeTools::isCHMode(mode) && channel->isCHModeSet(mode)) || (ft::ModeTools::isCHflag(mode)))
		{
			std::cout << "Remove the channel mode" << std::endl;
			if (!channel->removeChannelMode(mode, param))
			{
				std::string errmsg = ERR_USERNOTINCHANNEL(this->_server->getServerName(), param, channel->getChName());
				this->_client->sendReply(errmsg);
				std::cout << "Errmsg: not a member" << std::endl;
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
		if (!ft::ModeTools::isCHMode(this->modes[MODE][i]) && !ft::ModeTools::isMEMode(this->modes[MODE][i]) && !ft::ModeTools::isCHflag(this->modes[MODE][i]))
		{
			// ! ErrMsg unknown channel mode
			std::string mode = "";
			mode += this->modes[MODE][i];
			std::string errmsg = ERR_UNKNOWNMODE(this->_server->getServerName(), this->_client->getNickName(), mode, _message->getParameter()[0]);
			this->_client->sendReply(errmsg);
			std::cout << BRED << "ErrMsg: " << this->modes[MODE][i] << " not a channel mode" << DEFCOLO << std::endl;
		}
		else if (!ft::ModeTools::isParamMode(this->modes[MODE][i]) || (this->modes[ACTION][i] == REMOVE && this->modes[MODE][i] == 'k') || (this->modes[ACTION][i] == REMOVE && this->modes[MODE][i] == 'l'))
			actionToChangeCHMode(this->modes[MODE][i], "", this->modes[ACTION][i]);
		else
		{
			/*
				? this meant for modes that need param like (o, v, k, l)
				? if there were more than one param mode in required pM_count will increment
				? so that it can point at the next position for the paramter
			*/
			if ((size_t)(MODEPARAMPOS + pM_count) >= this->_message->getParameter().size())
			{ 
				// ! ErrMsg more param needed for mode
				std::string errmsg = ERR_NEEDMOREPARAMS(this->_server->getServerName(), this->_client->getNickName(), this->_message->getCommand());
				this->_client->sendReply(errmsg);
				std::cout << BRED << "ErrMsg: " << this->modes[MODE][i] << " Need more params " << DEFCOLO << std::endl;
				continue ;
			}
			std::string param = this->_message->getParameter()[MODEPARAMPOS + pM_count];
			pM_count++;
			actionToChangeCHMode(this->modes[MODE][i], param, this->modes[ACTION][i]);
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
		std::cout << BRED << "ErrMsg: Not a channel operator\n" << DEFCOLO;
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
			std::cout << "The channel mode now is (" << channel->getCHMode() << ")" << std::endl;
		}
		else
		{
			// ! asking to change the mode or query about the mode
			this->initModes(this->_message->getParameter()[1]);
			this->checkCHModeCases(channel);
			std::cout << "The channel mode now is (" << channel->getCHMode() << ")" << std::endl;
		}
	}
	else
	{
		// ! send err channel doesn't exist
		std::string errMsg = ERR_NOSUCHCHANNEL(_server->getServerName(), _client->getNickName(), this->_message->getParameter()[0]);
		this->_client->sendReply(errMsg);
		std::cout << BRED << "ErrMsg: No Such a channel" << DEFCOLO << std::endl;
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
	if (_client)
	{
		std::cout << BBLU << "Mode executed" << DEFCOLO << std::endl;
		if (_client->getNickName() == "")
		{
			_client->sendReply("431 :No nickname given");
			return;
		}
		if (this->_message->getParameter().size() < 1)
		{
			_client->sendReply(ERR_NEEDMOREPARAMS(_server->getServerName(), _client->getNickName(), _message->getCommand()));
			return ;
		}
		if (this->_message->getParameter()[0][0] == '#')
			ChannelMode();
		this->modes.clear();
	}
}

