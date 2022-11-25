/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Message.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isaad <isaad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 19:26:45 by aaljaber          #+#    #+#             */
/*   Updated: 2022/11/25 22:43:09 by isaad            ###   ########.fr       */
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
			int _owner_fd;
			std::string	_msg;
			std::string *_Command;
			int			cmdCount; // number of parameters needed for the commands, taken from the parse
			std::string f_Command;
			std::string	_Parameter;
			std::string _Prefix;
			std::string _Trailing;
			std::string _channel;
			time_t		_time;

			//privet methods
			void 		parseMessage(std::string const &msg);
		public:
			Message(std::string const _msg, int _owner_fd);
			~Message();

			//methods
			std::string *getCommand();
			std::string getParameter();
			std::string getPrefix();
			std::string getTrailing();
			int			getCmdCount(); // needed for the commands
			int 		gerOwnerFd();
			bool 		isValid();
			bool 		isCommand();
			bool 		isPrefix();
			bool 		isParameter();
			bool 		isTrailing();

	};
}

#endif