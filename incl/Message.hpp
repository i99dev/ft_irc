/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Message.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oal-tena <oal-tena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 19:26:45 by aaljaber          #+#    #+#             */
/*   Updated: 2022/11/15 18:53:05 by oal-tena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MESSAGE_HPP
#define MESSAGE_HPP
#include <iostream>

/*
! used for message parsing
*/
namespace ft
{
	class Message
	{
		private:
			std::string	_msg;
			std::string _Command;
			std::string	*_Parameter;
			int			_ParaNum;
		public:
			std::string	getMsg(void) const;
			std::string	getCommand(void) const;
			std::string	*getParameter(void) const;
			int			getParaNum(void) const;
			void 		ParseMsg();
			Message(std::string _msg);
			~Message();
	};
}

#endif