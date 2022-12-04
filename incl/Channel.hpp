/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 13:26:10 by aaljaber          #+#    #+#             */
/*   Updated: 2022/12/04 05:31:13 by aaljaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP

#define CHANNEL_HPP

#include <string>
#include <vector>
#include <iostream>
#include "./Client.hpp"
// #include "./Mode_List.hpp"
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
			bool								_ChName_parse(std::string &name);
			ft::Client							*_getClientinfo(int ownerFD);

		public:

			// * Constructor and Destructor * //
			Channel(ft::Client *user, std::string &name);
			~Channel();
		
			// * Channel members * //
			std::vector<ft::Channel_Member>		members;

			// * Getters * //
			std::string							getChName(void);
			std::string							getpassword(void);
			std::vector<ft::Channel_Member>		getMembers(void);
			ft::Client							*getCreator(void);
			std::string							getTopic(void);
			std::vector<ft::Client *>			getUsers(void);
			
			// * Channel actions * //

			// ? JOIN
			void								addUser(ft::Client *user);
			
			// ? MODE
			void								setChannelMode(char mode);
			void								setMemberMode(Client *user, char mode);
			void								removeChannelMode(char mode);
			void								removeMemberMode(Client *user, char mode);
			void								makeMemberOperator(Client *user);
			void								makeMemberVoice(Client *user);
			void								setPassword(std::string &password);
			void								setTopic(std::string &topic);
			ft::Channel_Mode					findMode(char mode);
			bool								isChannelModerated(void);
			bool								isChannelInvitedOnly(void);
			bool								isChannelPrivate(void);
			bool								isCHModeSet(char mode);
			std::string							getCHMode(void);
			// ? PART
			void								removeUser(int userFD);
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
