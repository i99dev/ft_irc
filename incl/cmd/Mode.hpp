/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mode.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 06:47:44 by oal-tena          #+#    #+#             */
/*   Updated: 2022/12/03 02:54:29 by aaljaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MODE_HPP

#define MODE_HPP

#include "./Command.hpp"
#define	ACTION 0
#define	MODE 1

namespace ft
{
    class Command;
    class Mode : public Command
    {
    public:
        Mode(void);
		std::vector <std::string>	modes;
        void						execute(void);
		void						ChannelMode(void);
		void						UserMode(void);
		void						initModes(std::string mode);
		int							nextMode(std::string mode, int begin);
		void						changeUSMode(void);
    };
}

#endif