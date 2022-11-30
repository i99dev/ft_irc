/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oal-tena <oal-tena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 13:26:10 by aaljaber          #+#    #+#             */
/*   Updated: 2022/11/30 15:51:08 by oal-tena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP

#define CHANNEL_HPP

#include <string>
#include <vector>
#include <iostream>
#include "Client.hpp"
#include "Server.hpp"
#define CHNAME_LENGTH 50
#define EXC_WRONG_CHNAME "Wrong Channel Name"
#define	MODE_NUM 11
#define MODE_CHAR (char []){'C', 'N', 'O', 'o', 'v', 'i', 'm', 'p', 't', 'k', 'l'}
#define MODE_ENUM (Channel_Mode []){CLEAR_MODE, NO_MODE, O_CHANNEL_CREATOR, o_OPERATOR_PRIVILEGE, v_VOICE_PRIVILEGE,i_INVITE_ONLY_CHANNEL, m_MODERATED_CHANNEL, p_PRIVATE_CHANNEL, t_TOPIC, k_CAHNNEL_PASSWORD, l_USER_LIMIT}

class Client;

namespace ft
{
	enum Channel_Mode
	{
		CLEAR_MODE,
		NO_MODE,
		O_CHANNEL_CREATOR,
		o_OPERATOR_PRIVILEGE,
		v_VOICE_PRIVILEGE,
        i_INVITE_ONLY_CHANNEL, //? invite-only channel flag;
		m_MODERATED_CHANNEL, //? moderated channel flag;
        p_PRIVATE_CHANNEL, //? private channel flag;
        t_TOPIC, // ? topic;
        k_CAHNNEL_PASSWORD, //? set/remove(+/-) the channel key (password);
		l_USER_LIMIT, //? set/remove(+/-) the user limit to channel;
		
 	};
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
			ft::Channel_Mode					FindMode(char mode);
			
			// * Channel actions * //

			// ? PRIVMSG
			void								sendMsgtoChannel(Message *message);
			std::string							sendMsgFormat(Message *message);

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
			
			// ? PART
			void								removeUser(int userFD);
			std::vector<ft::Client *>			getMe(void);
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
