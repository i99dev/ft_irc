/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 19:17:08 by aaljaber          #+#    #+#             */
/*   Updated: 2022/12/01 02:21:08 by aaljaber         ###   ########.fr       */
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
#include "Mode_List.hpp"

namespace ft
{
	class Client
	{
		private:
			std::string					_nickName;
			std::string					_userName;
			std::vector <Message *>		_msgSend;
			std::vector <Message *>		_msgRecv;
			std::string					_client_ip;
			bool                 		_is_authenticated;
			bool                 		_is_ope;
			int                  		_ping;
			std::vector <ft::User_Mode>	_mode;
			//ip 
			 
			
		public:
			int						fd;
			//user info
			std::string				getNickName(void)const;
			void 					setNickName(std::string nickName);
			std::string				getUserName(void)const;
			void 					setUserName(std::string userName);
			//user channels
			std::string				getChannelsJoined(void)const;
			void 					setChannelsJoined(std::string channelsJoined);
			// user ip 
			std::string				getIp(void)const;
			// user massage
			std::vector <Message *>	getMsgSend(void)const;
			void 					setMsgSend(Message  *msgSend);
			std::vector <Message *>	getMsgRecv(void)const;
			void 					setMsgRecv(Message *msgRecv);
			void 					sendReply(std::string reply);

			//ping 
			int						getPing(void)const;
			void 					setPing(int ping);
			
			// user mode
			bool					isOperator(void);
			bool					isInvisible(void);
			void					setUserMode(char mode);
			void					removeUserMode(char mode);
			ft::User_Mode			findMode(char mode);

			Client(int &fd, std::string servername, std::string ip);
			~Client();
	};
}

#endif