/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Whois.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oal-tena <oal-tena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 06:55:45 by oal-tena          #+#    #+#             */
/*   Updated: 2022/11/30 07:04:44 by oal-tena         ###   ########.fr       */
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
    std::cout << "Whois executed" << std::endl;
}