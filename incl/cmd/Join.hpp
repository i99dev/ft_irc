#ifndef JOIN_HPP

#define JOIN_HPP

#include <iostream>
#include <vector>
#include "../Channel.hpp"
#include "../Server.hpp"
#include "../Client.hpp"

class Join{
	private:
			std::string name;
	public:
		Join(ft::Client *client, std::vector<ft::Channel *> &channels){
			if (check_params(client)){
				// if (check_existence(channels, int(channels.size())))
					// join channel
				// else
					// create channel
			}
				
		}

		bool	check_params(ft::Client *client){
			if (client->getMsgSend().back().getCommand() == "JOIN"){
				name = getChannelName(client);
				if (name.empty() == false && name[0] != 0)
					return true;
				else
					std::cout << "ERROR: incorrect number of arguments" << std::endl;
			}
			return false;
		}

		std::string	getChannelName(ft::Client *client){
			int i = 0;
			int j = 1;
			char *s;

			client->getMsgSend().back().getParameter().copy(s, client->getMsgSend().back().getParameter().length() - 3, 1);
			return s;
		}

		bool	check_existence(std::vector<ft::Channel *> channels, int channel_size){
			for (int i = 0; i < channels.size(); i++){
				if (channels[i]->getName() == name)
					return true;
			}
			return false;
		}
};

#endif