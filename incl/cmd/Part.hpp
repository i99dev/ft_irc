/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Part.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isaad <isaad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 19:58:17 by oal-tena          #+#    #+#             */
/*   Updated: 2022/12/01 02:43:31 by isaad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef PART_HPP

#define PART_HPP

#include "./Command.hpp"
#include "../Replies.hpp"

namespace ft
{
	class Part : public ft::Command
	{
	public:
		Part(void);
		void execute();
	};

}

#endif
