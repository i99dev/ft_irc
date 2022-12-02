/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 06:56:51 by oal-tena          #+#    #+#             */
/*   Updated: 2022/12/02 15:18:34 by aaljaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/cmd/Mode.hpp"

ft::Mode::Mode()
{
    _name = "Mode";
    _description = "Change user or channel mode";
    _usage = "/mode <channel> <mode> [<mode> ...]";
}

void	ft::Mode::ChannelMode(void)
{
	
}

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

void	ft::Mode::UserMode(void)
{
	if (this->_message->getParameter().size() < 2)
	{
		std::string errMsg = ERR_NEEDMOREPARAMS(this->_server->getServerName(), this->_client->getNickName(), this->_message->getCommand());
		this->_client->sendReply(errMsg);
		return ;
	}
	std::cout << this->_client->getNickName() << " " << this->_message->getParameter()[0] << std::endl;
	if (this->_message->getParameter()[0] == this->_client->getNickName())
	{
		initModes(this->_message->getParameter()[1]);
		std::cout << "action " << modes[0] << std::endl;
		std::cout << "mode " << modes[1] << std::endl;
	}
	else
	{
		std::cout << "no match" << std::endl;
		// std::stringstream stream;
		// stream << ERR_USERSDONTMATCH;
		// std::string errMsg;
		// stream >> errMsg;
		// std::string errMsg = std::to_string(ERR_USERSDONTMATCH);
		this->_client->sendReply(ERR_USERSDONTMATCH);
	}
}

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

