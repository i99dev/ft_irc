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
				std::vector<std::string> cmd;
				std::vector<std::string> channels;
				int			Count;
				std::vector<std::string> passwords;
				int			index;
		public:
			Join(ft::Client *client, std::vector<ft::Channel *> &channels);

			void		getChannelName(ft::Client *client);
			void		getPassword(int j, int start, int size, char *s);
			bool		check_cmd(ft::Client *client);
			bool		check_exist(std::vector<ft::Channel *> channels);
			ft::Channel *getExistingCh(std::vector<ft::Channel *> channels, int index);
			~Join();
	};
}

#endif
