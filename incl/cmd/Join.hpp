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
				std::string name;
		public:
			Join(ft::Client *client, std::vector<ft::Channel *> &channels);

			bool	check_params(ft::Client *client);
			std::string	getChannelName(ft::Client *client);
			bool	check_exist(std::vector<ft::Channel *> channels, int channel_size);
			~Join();
	};
}

#endif