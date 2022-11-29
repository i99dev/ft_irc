/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Join.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oal-tena <oal-tena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 19:58:17 by oal-tena          #+#    #+#             */
/*   Updated: 2022/11/29 07:50:00 by oal-tena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef JOIN_HPP

#define JOIN_HPP

#include "./Command.hpp"

namespace ft
{
	class Join : public ft::Command
	{
	public:
		Join(void);
		void execute();
	};

}

#endif
