/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Nick.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oal-tena <oal-tena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 00:12:53 by oal-tena          #+#    #+#             */
/*   Updated: 2022/11/29 00:14:13 by oal-tena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NICK_HPP
#define NICK_HPP

#include "./Command.hpp"

namespace ft
{
	class Nick : public ft::Command
	{
	public:
		Nick(void);
		void execute();
	};

}
#endif