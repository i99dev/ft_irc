/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mode.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 06:47:44 by oal-tena          #+#    #+#             */
/*   Updated: 2022/12/01 19:13:05 by aaljaber         ###   ########.fr       */
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
        void	execute();
		void	ChannelMode(void);
		void	UserMode(void);
    };
}

#endif