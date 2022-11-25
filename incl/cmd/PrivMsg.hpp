#ifndef PRIVMSG_HPP

#define PRIVMSG_HPP

#include "../Channel.hpp"
#include "../Client.hpp"

namespace ft{
	class PRIVMSG{
		private:
			std::string *cmd; // full cmd array
			std::string ChName; // name of channel string
			std::string msg; // pure message to send to channel
			ft::Channel *target; // target channel to send message on
			int			cmdCount; // helper for my functions
		public:
			PRIVMSG(std::vector<ft::Channel *> channels, Client *client);

			void	execute(Client *client);

			bool    check_cmd(ft::Client *client);

			void	getChName(Client *client);

			void	getChannel(std::vector<ft::Channel *> channels);

			void	getMsg();
	};
}

#endif