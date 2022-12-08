/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Message.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oal-tena <oal-tena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 19:26:45 by aaljaber          #+#    #+#             */
/*   Updated: 2022/12/08 17:53:46 by oal-tena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MESSAGE_HPP
#define MESSAGE_HPP
#include <iostream>
#include <vector>
#include <map>
struct _mask
{
	std::string nick;
	std::string user;
	std::string host;
	std::string wildcard; //use ex : general* or *general
} typedef t_mask;

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
			std::vector<t_mask *>		_masks;

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
			bool		is_wildCard(std::string const &str);
			bool		match_wildCard(std::string const &str, std::string const &wildcard);
			void		split_mask(std::string &str);
			bool		is_mask();
			bool		match_client_mask(ft::Client *client);
	};
}

#endif
