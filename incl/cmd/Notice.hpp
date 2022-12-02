/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Notice.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isaad <isaad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 00:12:53 by oal-tena          #+#    #+#             */
/*   Updated: 2022/12/01 03:52:37 by isaad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NOTICE_HPP
#define NOTICE_HPP

#include "./Command.hpp"
#include "../Replies.hpp"

namespace ft
{
	class Notice : public ft::Command
	{
	public:
		Notice(void);
		void execute();
	};

}
#endif