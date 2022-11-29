#ifndef CHANNEL_HPP

#define CHANNEL_HPP

#include <string>
#include <vector>
#include <iostream>
#include "Client.hpp"
#define CHNAME_LENGTH 50
#define EXC_WRONG_CHNAME "Wrong Channel Name"

class Client;

enum ChannelMode{
	CHANNEL_MODEPRIVATE = 0,
	CHANNEL_MODE_SECRET = 1,
	CHANNEL_MODE_INVITE_ONLY = 2,
	CHANNEL_MODE_MODERATED = 3,
	CHANNEL_MODE_TOPIC_SETTABLE_BY_CHANNEL_OPERATOR_ONLY = 4,
	CHANNEL_MODE_CANT_SENT_MESSAGES_OUTSIDE = 5,
	CHANNEL_MODE_BAN_MASK = 6,
	CHANNEL_MODE_KEY = 7
};

namespace ft
{
	class Channel{
		private:
			Client						*_creator;
			std::string					_name;
			time_t						_created_at;
			size_t						_max_clients;
			ChannelMode					_mode;
			std::string					_password;
			std::string					_topic;
			int							_ChName_parse(std::string &name)
			{
				if (name[0] == '&' || name[0] == '#' || name[0] == '+' || name[0] == '!')
				{
					if (name.find('&', 1) == std::string::npos && name.find('#', 1) == std::string::npos && name.find('+', 1) == std::string::npos && name.find('!', 1) == std::string::npos)
					{
						if (name.length() <= CHNAME_LENGTH)
						{
							if (name.find(' ') == std::string::npos && name.find(':') == std::string::npos && name.find(',') == std::string::npos && name.find(7) == std::string::npos)
								return (1);
						}
					}
				}
				return(0);
			}
		public:
			std::vector<Client *>	_normal_clients;
			std::vector<Client *>	_ope_clients;
		public:
			// Channel(Client *user, std::string &name);
			Channel(std::string &name, std::string &password);
			std::string					getChName(void);
			void						sendMsgtoChannel(Message *message);
			void						addClient(Client *user);
			std::vector<Client *>		getClients() const;
			ChannelMode					getMode();
			ChannelMode					addMode(ChannelMode mode);
			ChannelMode					removeMode(ChannelMode mode);
			std::string					&getPassword();
			std::string					&getName();
			std::string					&getTopic();
			std::string					getModeString();
			std::string					getClientRoleString(Client *client);
			Client						&getCreator();
			time_t						&getCreatedAt();
			size_t						&getMaxClients();
			bool						joined(Client *client);
			bool						isOwner(Client *client);
			bool						isOpe(Client *client);
			bool						isNormal(Client *client);
			bool						isVoice(Client *client);
			void						setCreator(Client *creator);
			void						removeClientFromChannel(Client *client);
		~Channel();
	};
}

class WrongChannelNameRequir : public std::exception
{
	public:
		const char* what() const throw()
		{
			return (EXC_WRONG_CHNAME);
		}
};

#endif
