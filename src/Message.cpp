/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Message.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oal-tena <oal-tena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 19:55:02 by aaljaber          #+#    #+#             */
/*   Updated: 2022/11/28 20:03:51 by oal-tena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/Message.hpp"
#include "../incl/cmd/PrivMsg.hpp"

/******************* GETTERS *******************/
/**
 * @brief Parse the message received from the client
 *
*/
void ft::Message::parseMessage(std::string const &msg)
{
	//irc parsing msg here
// std::cout << "msg: " << msg << std::endl;
	int i = 0;
	if (msg[i] == ':')
	{
		i++;
		while (msg[i] != ' ' && msg[i])
		{
			this->_Prefix += msg[i];
			i++;
		}
		i++;
	}
	while (msg[i] != ' ' && msg[i])
	{
		this->_Command += msg[i];
		i++;
	}
	i++;
	while (msg[i] != ' ' && msg[i])
	{
		this->_Parameter.push_back(std::string());
		while (msg[i] != ' ' && msg[i])
		{
			this->_Parameter.back() += msg[i];
			i++;
		}
		i++;
	}
	if (msg[i] == ':')
	{
		i++;
		while (msg[i])
		{
			this->_Parameter.push_back(std::string());
			while (msg[i] != ' ' && msg[i])
			{
				this->_Parameter.back() += msg[i];
				i++;
			}
			i++;
		}
	}
	//cout 
	std::cout << "Command: " << _Command << std::endl;
	std::cout << "Prefix: " << _Prefix << std::endl;
	for (size_t i = 0; i < _Parameter.size(); i++)
	{
		std::cout << "Parameter: " << _Parameter[i] << std::endl;
	}
}

ft::Message::Message(std::string msg,int owner_fd){
	this->_owner_fd = owner_fd;
	this->_msg = msg;
	parseMessage(msg);
}

ft::Message::~Message(){
}

int ft::Message::gerOwnerFd(){
	return _owner_fd;
}

std::string ft::Message::getCommand(){
	return _Command;
}

std::vector<std::string> ft::Message::getParameter(){
	return _Parameter;
}

std::string ft::Message::getPrefix(){
	return _Prefix;
}


bool ft::Message::isValid(){
	return true;
}

// bool ft::Message::isCommand(){
// 	if (_Command.empty())
// 		return false;
// 	return true;
// }

bool ft::Message::isPrefix(){
	if (_Prefix.empty())
		return false;
	return true;
}

bool ft::Message::isParameter(){
	if (_Parameter.empty())
		return false;
	return true;
}



