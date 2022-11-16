/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Message.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oal-tena <oal-tena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 19:55:02 by aaljaber          #+#    #+#             */
/*   Updated: 2022/11/16 06:10:06 by oal-tena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/Message.hpp"

/******************* GETTERS *******************/

std::string	ft::Message::getMsg(void) const
{
	return(this->_msg);	
}

std::string	ft::Message::getCommand(void) const
{
	return(this->_Command);
}

std::string	*ft::Message::getParameter(void) const
{
	return(this->_Parameter);
}

int			ft::Message::getParaNum(void) const
{
	return(this->_ParaNum);
}

ft::Message::Message(std::string msg):_msg(msg){
	this->ParseMsg();
}

ft::Message::~Message(){}


/**
 * @brief Parse the message and store the command and parameters
 * 
 * @return void
*/
void ft::Message::ParseMsg()
{
	std::string		*tmp;
	std::string		*tmp2;
	int				i;
	int				j;

	i = 0;
	j = 0;
	tmp = new std::string[15];
	tmp2 = new std::string[15];
	while (this->_msg[i] != '\0')
	{
		if (this->_msg[i] == ' ')
		{
			tmp[j] = this->_msg.substr(0, i);
			this->_msg = this->_msg.substr(i + 1, this->_msg.length());
			i = 0;
			j++;
		}
		else
			i++;
	}
	tmp[j] = this->_msg;
	this->_Command = tmp[0];
	this->_ParaNum = j;
	for (int i = 0; i < j; i++)
		tmp2[i] = tmp[i + 1];
	this->_Parameter = tmp2;
	//print 
	std::cout << "Command: " << this->_Command << std::endl;
	std::cout << "Parameters: " << this->_Parameter[0] << std::endl;
}