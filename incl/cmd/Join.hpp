#ifndef JOIN_HPP

#define JOIN_HPP

#include <iostream>
#include <vector>
#include "../Channel.hpp"
#include "../Server.hpp"
#include "../Client.hpp"

namespace ft{
	class Join{
		private:
				std::string *cmd;
				std::string *channels;
				std::string channel;
				int			Count;
				std::string *passwords;
				std::string password;
				int			index;
		public:
			Join(ft::Client *client, std::vector<ft::Channel *> &channels);

			void		getChannelName(ft::Client *client);
			bool		check_cmd(ft::Client *client);
			bool		check_exist(std::vector<ft::Channel *> channels);
			ft::Channel *getExistingCh(std::vector<ft::Channel *> channels, int index);
			~Join();
	};
}

#endif