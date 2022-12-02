/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Whois.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isaad <isaad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 06:55:45 by oal-tena          #+#    #+#             */
/*   Updated: 2022/12/03 02:00:42 by isaad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/cmd/Whois.hpp"

ft::Whois::Whois()
{
	_name = "Whois";
	_description = "Get information about a user";
	_usage = "/whois <nickname>";
}

void ft::Whois::execute()
{
	// _client->sendReply(RPL_LISTSTART(_server->getServerName(), _message->getParameter()[0]));
	// _client->sendReply(RPL_LIST(_client->getServerName(), _client->getNickName(), "smth", "many", "topic"));
	std::cout << "Whois executed" << std::endl;
}