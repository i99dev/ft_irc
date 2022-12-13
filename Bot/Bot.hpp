/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bot.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isaad <isaad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 10:58:57 by oal-tena          #+#    #+#             */
/*   Updated: 2022/12/13 06:34:05 by isaad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BOT_HPP
#define BOT_HPP

#include <iostream>
#include <string>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

namespace ft
{
	class Bot{
		private:
			std::string _nickname;
			std::string	port;
			std::string msg;
			int			sockfd;
			char *		host;
			std::string	sender;
		public:
			Bot(std::string, char *);
			void		generateNickName();
			void		doProcess();
			void		reply();
			void		sendToServer(std::string);
			std::string receiveFromServer();
			void		loop();
			~Bot();
	};
} 

#endif