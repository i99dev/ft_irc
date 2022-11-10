/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 19:17:08 by aaljaber          #+#    #+#             */
/*   Updated: 2022/11/09 20:02:29 by aaljaber         ###   ########.fr       */
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
		public:
			std::string				getNickName(void)const;
			std::string				getUserName(void)const;
			std::string				getChannelsJoined(void)const;
			std::vector <Message>	getMsgSend(void)const;
			std::vector <Message>	getMsgRecv(void)const;
			Client();
			~Client();
	};
}

#endif