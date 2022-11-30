/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Whois.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oal-tena <oal-tena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 06:46:59 by oal-tena          #+#    #+#             */
/*   Updated: 2022/11/30 06:54:16 by oal-tena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WHOIS_HPP

#define WHOIS_HPP

#include "./Command.hpp"

namespace ft
{
    class Command;
    class Whois : public Command
    {
    public:
        Whois(void);
        void execute();
    };
}

#endif