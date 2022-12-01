/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isaad <isaad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 19:17:08 by aaljaber          #+#    #+#             */
/*   Updated: 2022/12/01 20:30:22 by isaad            ###   ########.fr       */
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


namespace ft
{
	class Client
	{
		private:
			std::string				_nickName;
			std::string				_userName;
			std::string				_serverName;
			std::string				_realName;
			std::string				_hostName;
			std::vector <Message *>	_msgSend;
			std::vector <Message *>	_msgRecv;
			std::string				_client_ip;
			bool                 	_is_authenticated;
			bool                 	_is_ope;
			int                  	_ping;
			//ip 
			 
			
		public:
			int						fd;
			//user info
			std::string				getNickName(void)const;
			void 					setNickName(std::string nickName);
			std::string				getUserName(void)const;
			void 					setUserName(std::string userName);
			std::string				getServerName(void)const;
			void 					setServerName(std::string serverName);
			std::string				getRealName(void)const;
			void 					setRealName(std::string realName);
			std::string				getHostName(void)const;
			void 					setHostName(std::string hostName);
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
			
			Client(int &fd, std::string servername, std::string ip);
			~Client();
	};
}

#endif