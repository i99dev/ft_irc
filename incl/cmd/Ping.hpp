/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ping.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oal-tena <oal-tena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 07:05:46 by oal-tena          #+#    #+#             */
/*   Updated: 2022/11/30 07:06:10 by oal-tena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PING_HPP

#define PING_HPP

#include "./Command.hpp"

namespace ft
{
    class Command;
    class Ping : public Command
    {
    public:
        Ping(void);
        void execute();
    };
}

#endif