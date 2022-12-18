/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 13:26:10 by aaljaber          #+#    #+#             */
/*   Updated: 2022/12/19 00:30:36 by aaljaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP

#define CHANNEL_HPP

#include <string>
#include <vector>
#include <iostream>
#include "./Client.hpp"
// #include "./Mode_List.hpp"
#include <cstdarg>
#define CHNAME_LENGTH 50
#define EXC_WRONG_CHNAME "Wrong Channel Name"

class Client;

namespace ft
{
	struct Channel_Member
	{
		ft::Client								*user;
		ft::Channel_Mode						user_mode;
	};
	class Channel
	{	
		private:
			std::string							_name;
			std::vector<ft::Channel_Mode>		_mode;
			time_t								_created_at;
			std::string							_password;
			std::string							_topic;
			int									_limit;
			bool								_ChName_parse(std::string &name);
			std::vector<ft::WildCard *>			_banList;
			std::vector<ft::WildCard *>			_invitedList;
			std::vector<ft::WildCard *>			_exceptionList;

		public:

			// * Constructor and Destructor * //
			Channel(ft::Client *user, std::string &name);
			~Channel();
		
			// * Channel members * //
			std::vector<ft::Channel_Member>	members;

			// * Getters * //
			std::string						getChName(void);
			std::string						getpassword(void);
			std::vector<ft::Channel_Member>	getMembers(void);
			ft::Client						*getCreator(void);
			std::string						getTopic(void);
			std::vector<ft::Client *>		getUsers(void);
			ft::Client						*getMember(std::string nick);
			
			// * Channel actions * //

			// ? JOIN
			void							addUser(ft::Client *user);
			
			// ? MODE
			int								setChannelMode(char mode, std::string param);
			int								setMemberMode(Client *user, char mode);
			int								removeChannelMode(char mode, std::string param);
			int								removeMemberMode(Client *user, char mode);
			void							setPassword(std::string &password);
			void							setTopic(std::string &topic);
			void							setTopic(int num);
			ft::Channel_Mode				findMode(char mode);
			bool							isCHModeSet(char mode);
			bool							isMEModeSet(Client *user, char mode);
			std::string						getCHMode(void);
			bool							isMember(int OwnerFD);
			bool							isMember(std::string nick);
			bool							isMemberOperator(int OwnerFD);
			// ? PART
			void							removeUser(int userFD);
	};
	class WrongChannelNameRequir : public std::exception
	{
		public:
			const char* what() const throw()
			{
				return (EXC_WRONG_CHNAME);
			}
	};
}


#endif
