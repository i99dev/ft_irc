/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 19:17:08 by aaljaber          #+#    #+#             */
/*   Updated: 2022/11/23 05:34:37 by aaljaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
#define CLIENT_HPP
#include <iostream>
#include <vector>
#include "Message.hpp"
#include "Channel.hpp"

class Channel;
/*
! used for 
	- registring the user
	- getting his info
	- storing his msg
*/

namespace ft
{
	class Client
	{
		private:
			std::string				_nickName;
			std::string				_userName;
			std::vector <Channel *>	_channelsJoined;
			std::vector <Message>	_msgSend;
			std::vector <Message>	_msgRecv;
			bool                 	_is_authenticated;
			bool                 	_is_ope;
			int                  	_attempts;
			
		public:
			int						fd;
			std::string							getNickName(void)const;
			std::string							getUserName(void)const;
			std::vector <Channel *>				getChannelsJoined(void)const;
			std::vector <Message>				getMsgSend(void)const;
			std::vector <Message>				getMsgRecv(void)const;
			void 								saveMsg(std::string msg)
			{
				Message msg_new = Message(msg);
				_msgSend.push_back(msg_new);
			}
			Client(int &fd);
			~Client();
	};
}

#endif