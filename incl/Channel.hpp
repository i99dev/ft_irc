/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 13:26:10 by aaljaber          #+#    #+#             */
/*   Updated: 2022/11/29 09:43:54 by aaljaber         ###   ########.fr       */
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
#define	MODE_NUM 6
#define MODE_CHAR (char []){'i', 'p', 's', 't', 'k', 'l'}
#define MODE_ENUM (Channel_Mode []){i_INVITE_ONLY_CHANNEL, p_PRIVATE_CHANNEL, s_SECRET_CHANNEL, t_TOPIC, k_CAHNNEL_PASSWORD, l_USER_LIMIT}

class Client;

namespace ft
{
	enum Channel_Mode
	{
        i_INVITE_ONLY_CHANNEL, //? invite-only channel flag
        p_PRIVATE_CHANNEL, //? private channel flag;
        s_SECRET_CHANNEL, //? secret channel flag;
        t_TOPIC, // ? topic
        k_CAHNNEL_PASSWORD, //? set/remove(+/-) the channel key (password);
		l_USER_LIMIT, //? set/remove(+/-) the user limit to channel;
 	};
	class Channel
	{	
		private:

			ft::Client					*_creator;
			std::string					_name;
			time_t						_created_at;
			std::vector<Channel_Mode>	_mode;
			std::string					_password;
			std::string					_topic;
			size_t						_max_clients;
			bool						_ChName_parse(std::string &name);
			ft::Client					*_getSenderinfo(int ownerFD);

		public:

			// * Constructor and Destructor * //
			Channel(ft::Client *user, std::string &name);
			~Channel();
		
			// * Channel members * //
			std::vector<ft::Client *>	users;
			std::vector<ft::Client *>	operators;

			// * Getters * //
			std::string					getChName(void);
			std::string					getpassword(void);
			
			// * Channel actions * //

			// ? PRIVMSG
			void						sendMsgtoChannel(Message *message);
			std::string					sendMsgFormat(Message *message);

			// ? JOIN
			void						addUser(ft::Client *user);
			void						addUser(ft::Client *user, std::string &password);
			
			// ? MODE
			void						setChannelMode(char mode);
			void						addChannelOperators(Client *user);		
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
