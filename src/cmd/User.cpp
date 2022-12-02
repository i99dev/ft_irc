/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oal-tena <oal-tena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 19:18:38 by oal-tena          #+#    #+#             */
/*   Updated: 2022/12/02 08:46:00 by oal-tena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/cmd/User.hpp"

ft::User::User()
{
    _name = "User";
    _description = "Set username";
    _usage = "/user <username>";
}

void ft::User::execute()
{
    _client->setUserName(_message->getParameter()[0]);
    _client->setHostName(_message->getParameter()[1]);
    _client->setServerName(_message->getParameter()[2]);
    _client->setRealName(_message->getParameter()[3]);
    std::cout << "User executed" << std::endl;
	for (long unsigned int i = 0; i < this->_message->getParameter().size(); i++)
		std::cout << i << " " << this->_message->getParameter()[i] << std::endl; 

}