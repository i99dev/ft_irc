/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Message.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 19:55:02 by aaljaber          #+#    #+#             */
/*   Updated: 2022/11/09 20:04:56 by aaljaber         ###   ########.fr       */
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

ft::Message::Message(std::string msg):_msg(msg){}

ft::Message::~Message(){}