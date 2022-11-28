/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oal-tena <oal-tena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 00:14:34 by oal-tena          #+#    #+#             */
/*   Updated: 2022/11/29 00:16:53 by oal-tena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/cmd/Nick.hpp"

ft::Nick::Nick(void)
{
    _name =  "Nick";
    _description = "Change your nickname or set it if you don't have one";
    _usage = "/nick <nickname>";
}

void ft::Nick::execute()
{
    std::cout << "Nick executed" << std::endl;
    _client->setNickName(_message->getParameter()[0]);
    //cout 
    std::cout << "Nickname changed to " << _client->getNickName() << std::endl;
}
