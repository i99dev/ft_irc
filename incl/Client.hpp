/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 19:17:08 by aaljaber          #+#    #+#             */
/*   Updated: 2022/12/30 10:30:27 by aaljaber         ###   ########.fr       */
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

# define BBLK "\e[1;30m"
# define BRED "\e[1;31m"
# define BGRN "\e[1;32m"
# define BYEL "\e[1;33m"
# define BBLU "\e[1;34m"
# define BMAG "\e[1;35m"
# define BCYN "\e[1;36m"

# define BWHT "\e[1;37m"
# define BPUR "\e[0;35m"
# define DEFCOLO "\033[0m"

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
			std::vector <ft::User_Mode>	_mode;
			//ip 
			 
			
		public:
			int							PASSFlag;
			int							fd;
			std::vector <std::string>	invites;
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
			int 					getSocket(void)const;
			void 					setSocket(int socket);
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
			void 					sendReply(int reply);

			//ping 
			int						getPing(void)const;
			void 					setPing(int ping);
			
			// user mode
			bool					isOperator(void);
			bool					isInvisible(void);
			bool					isUSModeSet(char mode);
			void					setUserMode(char mode);
			void					removeUserMode(char mode);
			std::string				getUSMode(void);
			
			std::string				intToString(int number);
			Client(int &fd, std::string servername, std::string ip);
			~Client();
	};
}

#endif