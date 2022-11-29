/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oal-tena <oal-tena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 19:18:38 by oal-tena          #+#    #+#             */
/*   Updated: 2022/11/29 00:10:48 by oal-tena         ###   ########.fr       */
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
    std::cout << "User executed" << std::endl;
}