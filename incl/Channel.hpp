#ifndef CHANNEL_HPP

#define CHANNEL_HPP

#include <string>
#include <vector>
#include <iostream>
#include "Client.hpp"
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

namespace ft{
	class Channel{
		private:
			ChannelMode					_mode;
			std::string					_password;
			std::string					_name;
			std::string					_topic;
			time_t						_created_at;
			size_t						_max_clients;
			Client						*_creator;
		public:
			std::vector<Client *>	_normal_clients;
			std::vector<Client *>	_voice_clients;
			std::vector<Client *>	_ope_clients;
		public:
			Channel(std::string &name,  std::string &password);
			std::vector<Client *>	getClients() const;
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
	};
}

#endif
