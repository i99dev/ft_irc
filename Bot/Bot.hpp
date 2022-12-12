/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bot.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isaad <isaad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 10:58:57 by oal-tena          #+#    #+#             */
/*   Updated: 2022/12/12 23:57:12 by isaad            ###   ########.fr       */
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
			int			sockfd;
			char *		host;
		public:
			Bot(std::string, char *);
			void		generateNickName();
			void		doProcess();
			void		sendToServer(std::string);
			std::string receiveFromServer();
			void		loop();
			~Bot();
	};
} 

#endif