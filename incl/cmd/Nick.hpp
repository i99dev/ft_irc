/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Nick.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 00:12:53 by oal-tena          #+#    #+#             */
/*   Updated: 2023/01/02 16:24:18 by aaljaber         ###   ########.fr       */
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
		bool isvalid();
		void	isNickNameAvailable(std::string nickName);
		void	connectClientBack();
		bool		isNickOwnerRegistered(std::string nickName);
	};

}
#endif