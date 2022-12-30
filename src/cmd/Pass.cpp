/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 10:10:38 by aaljaber          #+#    #+#             */
/*   Updated: 2022/12/30 10:14:31 by aaljaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/cmd/Pass.hpp"

ft::Pass::Pass()
{
    _name = "pass";
    _description = "";
    _usage = "";
}

void ft::Pass::execute()
{
    std::cout << "Pass executed" << std::endl;
	
}