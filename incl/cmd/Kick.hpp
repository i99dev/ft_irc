/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Kick.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isaad <isaad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 19:58:17 by oal-tena          #+#    #+#             */
/*   Updated: 2022/12/09 07:56:11 by isaad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef KICK_HPP

#define KICK_HPP

#include "./Command.hpp"

namespace ft
{
	class Kick : public ft::Command
	{
	public:
		Kick(void);
		void execute();
	};

}

#endif
