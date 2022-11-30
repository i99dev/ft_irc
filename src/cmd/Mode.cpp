/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 06:56:51 by oal-tena          #+#    #+#             */
/*   Updated: 2022/11/30 18:07:43 by aaljaber         ###   ########.fr       */
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
}
