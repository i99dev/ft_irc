/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bot.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isaad <isaad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 10:58:57 by oal-tena          #+#    #+#             */
/*   Updated: 2022/12/14 04:20:39 by isaad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BOT_HPP
#define BOT_HPP

#include <iostream>
#include <string>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define WLCM(format) format + "Hello! how you doing?"
#define HELP(format) format + "if you want to know the commands available, type commands available or tell commands! If you want the syntax with the description for the commands include the word syntax with the name of the command! NOTE: up to 3 commands at once only"
#define CMDLIST(format) format + "sure! USER-NICK-PING-PONG-QUIT-KILL-JOIN-PART-PRIVMSG-NOTICE-INVITE-KICK-MODE-WHOIS-LIST"

#define USER(format) format + "USER->Used to identify the user to the server and provide additional information about the user. This command is typically used when connecting to an IRC server for the first time. Syntax is /user <username> <hostname> <servername> <realname>"
#define NICK(format) format + "NICK->used to set or change a user's nickname. This command allows users to identify themselves on the network. Syntax is /nick [new_nickname]"
#define PING(format) format + "PING->used to check if the client is still connected to the server. Syntax is /ping <server>"
#define QUIT(format) format + "QUIT->used to disconnect from the server. Syntax is /quit [message]"
#define KILL(format) format + "KILL->used to forcibly disconnect a user from the server. This command can only be executed by a server operator or someone with the appropriate permissions. Syntax is /kill <nickname> <comment>"
#define JOIN(format) format + "JOIN->used to join a specified channel on an IRC server. Syntax is /join <channel>{,<channel>} [<key>{,<key>}]"
#define PART(format) format + "PART->allows a user to leave a channel. Syntax is /part <channel>{,<channel>}"
#define PRIVMSG(format) format + "PRIVMSG->allows users to send private messages to other users or channels. Syntax is /privmsg <receiver>{,<receiver>} <text to be sent> or /msg <receiver>{,<receiver>} <text to be sent>"
#define NOTICE(format) format + "NOTICE->used to send a message to a user or channel that is not considered to be a part of the normal conversation. Syntax is /notice <receiver>{,<receiver>} <text to be sent>"
#define INVITE(format) format + "INVITE->the invite command is used to invite a user to join a specific channel. Syntax is /invite <nickname> <channel>"
#define KICK(format) format + "KICK->The kick command in IRC is used to remove a user from a channel. This command can only be used by channel operators or those with the appropriate permissions. Syntax is /kick <channel> <user> [<comment>]"
#define TOPIC(format) format + "TOPIC->used to set or display the topic for a channel. When used without any arguments, it will display the current topic for the channel that the user is currently in. Syntax is /topic <channel> [<topic>]"
#define MODE(format) format + "MODE->used to set or modify the modes of a user or channel. Modes are settings that can be applied to users or channels to control their behavior and access. In brief, it is devided into two parts: user modes, and channel modes. Syntax is /mode <nickname> {[+|-]|i|w|s|o} or /mode <channel> {[+|-]|o|p|s|i|t|n|b|v} [<limit>] [<user>] [<ban mask>]"
#define WHOIS(format) format + "WHOIS->The whois command in IRC is used to display information about a specific user. When this command is used, the IRC server will return information such as the user's real name, hostname, and any channels they are currently a member of. Syntax is /whois <nickname>"
#define LIST(format) format + "LIST->used to view a list of channels on the current server. When this command is executed, the server responds with a list of channels, along with information such as the topic and the number of users in each channel. Syntax is /list [<channel>{,<channel>} [<server>]]"

namespace ft
{
	class Bot{
		private:
			std::string _nickname;
			std::string	port;
			std::string msg;
			std::string msgRecv;
			std::string toSend;
			std::string	sender;
			std::string format;
			int			sockfd;
			char *		host;
			static const int i = 105;
			static std::string jokes[i];
		public:
			Bot(std::string, char *);
			void		generateNickName();
			void		doProcess();
			void		getSender();
			void		getMsgRecv(int);
			void		reply();
			void		sendToServer(std::string);
			std::string receiveFromServer();
			void		loop();
			void		initFunc();
			std::vector<std::string (*)(std::string&, std::string&, std::string&)> func;
			std::string getJoke();
			
			~Bot();
	};
}

#endif