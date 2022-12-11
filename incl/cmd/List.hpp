/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   List.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isaad <isaad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 19:58:17 by oal-tena          #+#    #+#             */
/*   Updated: 2022/12/10 23:46:20 by isaad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef LIST_HPP

#define LIST_HPP

#include "./Command.hpp"

namespace ft
{
	class List : public ft::Command
	{
	public:
		List(void);
		void execute();
	};

}

#endif