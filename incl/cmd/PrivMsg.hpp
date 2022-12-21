/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PrivMsg.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 06:54:54 by oal-tena          #+#    #+#             */
/*   Updated: 2022/12/20 09:13:54 by aaljaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRIVMSG_HPP

#define PRIVMSG_HPP

#include "./Command.hpp"
#include "../Mask.hpp"

namespace ft{
	class Privmsg: public ft::Command{
		public:
			Privmsg();
			void	execute();

	};
}

#endif
