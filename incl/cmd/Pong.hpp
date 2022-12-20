/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pong.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oal-tena <oal-tena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 16:12:25 by oal-tena          #+#    #+#             */
/*   Updated: 2022/12/20 16:12:48 by oal-tena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef PONG_HPP

#define PONG_HPP

#include "./Command.hpp"

namespace ft
{
    class Command;
    class Pong : public Command
    {
    public:
        Pong(void);
        void execute();
    };
}

#endif