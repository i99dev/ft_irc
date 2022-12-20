/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Message.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 19:26:45 by aaljaber          #+#    #+#             */
/*   Updated: 2022/12/20 09:13:54 by aaljaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MESSAGE_HPP
#define MESSAGE_HPP
#include <iostream>
#include <vector>
#include <map>
#include "Mask.hpp"

/*
! used for message parsing
*/
namespace ft
{
	class Client;
	class Message
	{
		private:
			int 						_owner_fd;
			std::string					_msg;
			std::string					_Command;
			std::vector<std::string>	_Parameter;
			std::string 				_Prefix;
			std::string 				_channel;
			time_t						_time;

			//privet methods
			void 		parseMessage(std::string const &msg);
		public:
			Message(std::string const _msg, int _owner_fd);
			~Message();

			//methods
			std::string getCommand();
			std::vector<std::string> getParameter();
			std::string getTrailing();
			int			getCmdCount(); // needed for the commands
			int 		gerOwnerFd();
			bool 		isValid();
			bool 		isCommand();
			bool 		isParameter();
			bool 		isTrailing();
	};
}

#endif
