#ifndef PRIVMSG_HPP

#define PRIVMSG_HPP

#include "../Channel.hpp"
#include "Command.hpp"
#include "../Client.hpp"

namespace ft{
	class PRIVMSG: public ft::Command{
		private:
			std::vector<std::string>	cmd; // full cmd array
			std::string					ChName; // name of channel string
			std::string					msg; // pure message to send to channel
			ft::Channel					*target; // target channel to send message on
			bool	check_cmd(std::string s);
			void	getChannel(std::vector<ft::Channel *> channels);
		public:
			PRIVMSG();

			void	execute();

	};
}

#endif
