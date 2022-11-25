/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 13:26:10 by aaljaber          #+#    #+#             */
/*   Updated: 2022/11/25 23:28:04 by aaljaber         ###   ########.fr       */
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

class Client;

namespace ft
{
	class Channel{
		private:
			ft::Client		*_creator;
			std::string		_name;
			time_t			_created_at;
			size_t			_max_clients;
			std::string		_topic;
			bool				_ChName_parse(std::string &name)
			{
				if (name[0] == '&' || name[0] == '#' || name[0] == '+' || name[0] == '!')
				{
					if (name.find('&', 1) == std::string::npos && name.find('#', 1) == std::string::npos && name.find('+', 1) == std::string::npos && name.find('!', 1) == std::string::npos)
					{
						if (name.length() <= CHNAME_LENGTH)
						{
							if (name.find(' ') == std::string::npos && name.find(':') == std::string::npos && name.find(',') == std::string::npos && name.find(7) == std::string::npos)
								return (true);
						}
					}
				}
				return(false);
			}
		public:
		Channel(ft::Client *user, std::string &name);
			std::vector<ft::Client *>	users;
			std::string					getChName(void);
			void						sendMsgtoChannel(Message *message);
			void						addClient(ft::Client *user);
			std::vector<ft::Client *>	getClients() const;
			std::string					ChnMsgFormat(Message *message);
			ft::Client					*getSenderinfo(int ownerFD);
		~Channel();
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
