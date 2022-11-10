/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oal-tena <oal-tena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 19:17:08 by aaljaber          #+#    #+#             */
/*   Updated: 2022/11/10 18:42:49 by oal-tena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
#define CLIENT_HPP
#include <iostream>
#include <vector>
#include "Message.hpp"
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
			std::string				_channelsJoined;
			std::vector <Message>	_msgSend;
			std::vector <Message>	_msgRecv;
			bool                 	_is_authenticated;
			bool                 	_is_ope;
			int                  	_attempts;
			
		public:
			int						fd;
			std::string				getNickName(void)const;
			std::string				getUserName(void)const;
			std::string				getChannelsJoined(void)const;
			std::vector <Message>	getMsgSend(void)const;
			std::vector <Message>	getMsgRecv(void)const;
			void 					saveMsg(std::string msg)
			{
				Message msg_new = Message(msg);
				_msgSend.push_back(msg_new);
			}
			Client(int &fd);
			~Client();
	};
}

#endif