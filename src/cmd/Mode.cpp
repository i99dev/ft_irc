/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 06:56:51 by oal-tena          #+#    #+#             */
/*   Updated: 2022/12/01 03:17:29 by aaljaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/cmd/Mode.hpp"

ft::Mode::Mode()
{
    _name = "Mode";
    _description = "Change user or channel mode";
    _usage = "/mode <channel> <mode> [<mode> ...]";
}

void ft::Mode::execute()
{
    std::cout << "Mode executed" << std::endl;
	for (long unsigned int i = 0; i < this->_message->getParameter().size(); i++)
		std::cout << i << " " << this->_message->getParameter()[i] << std::endl; 
}
