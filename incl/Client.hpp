/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oal-tena <oal-tena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 19:17:08 by aaljaber          #+#    #+#             */
/*   Updated: 2022/11/21 17:24:13 by oal-tena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
#define CLIENT_HPP

// Main libraries
#include <algorithm>
#include <poll.h>
#include <unistd.h>

// Socket includes
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>


#include "Message.hpp"
# include"Replies.hpp"
#include <string>

#include <fstream>
#include <vector>

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
			//ip 
			 
			
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
			Client(int &fd, std::string servername);
			~Client();
	};
}

#endif