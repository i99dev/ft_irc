/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oal-tena <oal-tena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 13:26:10 by aaljaber          #+#    #+#             */
/*   Updated: 2022/12/25 17:17:39 by oal-tena         ###   ########.fr       */
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
		ft::Client									*user;
		ft::Channel_Mode							user_mode;
	};
	class Channel
	{	
		private:
			std::string								_name;
			std::vector<ft::Channel_Mode>			_mode;
			time_t									_created_at;
			std::string								_key;
			std::string								_topic;
			int										_limit;
			int										_totalMem;
			std::vector<ft::Mask *>					_bannedList;
			std::vector<ft::Mask *>					_invitedList;
			std::vector<ft::Mask *>					_exceptedList;
			bool									_ChName_parse(std::string &name);
			void									_addMembertoChannel(Client *user);
			int										_findMask(const std::vector<ft::Mask *>	&MasksList, t_mask *mask);
			

		public:

			// * Constructor and Destructor * //
			Channel(ft::Client *user, std::string &name);
			~Channel();
		
			// * Channel members * //
			std::vector<ft::Channel_Member *>			members;
		
			// * Getters * //
			std::string								getChName(void);
			std::string								getkey(void);
			std::vector<ft::Channel_Member *>			getMembers(void);
			ft::Client								*getCreator(void);
			std::string								getTopic(void);
			std::vector<ft::Client *>				getUsers(void);
			ft::Client								*getMember(std::string nick);
			std::vector<ft::Mask *>					getExceptionList(void);
			std::vector<ft::Mask *>					getInvitedList(void);
			std::vector<ft::Mask *>					getBannedList(void);
			
			// * Channel actions * //

			// ? JOIN
			void									addUser(ft::Client *user);
			bool									isUserBanned(ft::Client *client);
			bool									isUserInvited(ft::Client *client);
			bool									isUserExcepted(ft::Client *client);
			bool									isChannelFull();
			bool									isCorrectKey(std::string &key);
			
			// ? MODE
			int										setChannelMode(char mode, std::string param);
			int										setChannelFlag(char mode, std::string param);
			int										setMemberMode(Client *user, char mode);
			int										removeChannelMode(char mode, std::string param);
			int										removeMemberMode(Client *user, char mode);
			int										removeChannelFlag(char mode, std::string param);
			void									setKey(std::string &key);
			void									setTopic(std::string &topic);
			void									setTopic(int num);
			ft::Channel_Mode						findMode(char mode);
			bool									isCHModeSet(char mode);
			bool									isMEModeSet(Client *user, char mode);
			std::string								getCHMode(void);
			bool									isMember(int OwnerFD);
			bool									isMember(std::string nick);
			bool									isMemberOperator(int OwnerFD);
			bool									isRepeatedMask(const std::vector<ft::Mask *> &MasksList, t_mask *mask);
			// ? PART
			void									removeUser(int userFD);
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
