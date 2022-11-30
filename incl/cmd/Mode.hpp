/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mode.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oal-tena <oal-tena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 06:47:44 by oal-tena          #+#    #+#             */
/*   Updated: 2022/11/30 06:54:19 by oal-tena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MODE_HPP

#define MODE_HPP

#include "./Command.hpp"

namespace ft
{
    class Command;
    class Mode : public Command
    {
    public:
        Mode(void);
        void execute();
    };
}

#endif