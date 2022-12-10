#include "../../incl/cmd/Join.hpp"

ft::Join::Join(void)
{
    _name = "Join";
    _description = "Join a channel";
    _usage = "/join <channel> [key]";
}

void ft::Join::execute()
{
	int flag = 0;
    	// get channel ;ist from server
	std::vector<Channel *> channels = _server->getChannels();
	int Count = 1;



	char *s;
	std::string cmd = _message->getParameter()[0];
	std::vector<std::string> chName; // to store all channel names
	std::vector<std::string> passwords; // to store all passwords

	int j = 0;
	int size = 0;
	int start = 0;
	// count the number of channels written in one command
	for(int i = 0; i < int(cmd.size()); i++){
		if (cmd[i] == ',')
			Count++;
	}
	std::cout << "count: " << Count << std::endl;
	// loop to get all the channel names one by one
	for(int i = 0; i < Count; i++){
		size = 0;
		if (cmd[j] != ',' && cmd[j])
			start = j;
		while(j < int(cmd.size())){
			if (cmd[j] == ',')
				break ;
			j++;
			size++;
		}
		s = new char[size + 1];
		cmd.copy(s, size, start);
		s[size] = 0;
		chName.push_back(std::string(s));
		delete [] s;
		j++;
	}
	j = 0;
	start = 0;
	size = 0;
	if (_message->getParameter().size() > 1){
		cmd = _message->getParameter()[1];
		// loop to get all the passwords one by one
		for(int i = 0; i < Count; i++){
			size = 0;
			if (cmd[j] != ',' && cmd[j])
				start = j;
			while(j < int(cmd.size())){
				if (cmd[j] == ',')
					break ;
				j++;
				size++;
			}
			s = new char[size + 1];
			cmd.copy(s, size, start);
			s[size] = 0;
			passwords.push_back(std::string(s));
			delete [] s;
			j++;
		}
	}



	for (int i = 0; i < Count; i++){
		flag = 0;
		bool ok = false;
	    // get channel name from message
	    std::string channelName = chName[i];
	    // get channel key from message
	    std::string channelKey = "";
	    if (_message->getParameter().size() > 1)
	    {
			if (!passwords[i].empty()){
		        channelKey = passwords[i];
			}
	    }
	    // check if channel exists
	    // std::vector<Channel *>::iterator it;
	    for (int i = 0; i < int(channels.size()); i++)
	    {
	        if (channels[i]->getChName() == channelName)
	        {
				flag = 1;
				if (channels[i]->isCHModeSet('i')){
					for (int y = 0; y < _client->invites.size(); y++){
						if (_client->invites[y] == channelName){
							ok = true;
						}
					}
					if (!ok){
						_client->sendReply("-!- " + _client->getNickName() + ": Cannot join channel " + channelName + " (+i) - invite only");
						return ;
					}
				}
	            // check if channel has a key
	            if (channels[i]->getpassword() != "")
	            {
	                // check if key is correct
	                if (_message->getParameter()[1].size() > 1 && channels[i]->getpassword() == channelKey)
	                {
	                    // add client to channel
	                    channels[i]->addUser(_client);
	                    // send message to all clients in that channel
						std::vector<Client *> clients = (channels[i])->getUsers();
						std::vector<Client *>::iterator it2 = clients.begin();
						for (; it2 != clients.end(); it2++)
						{
							// std::string joinMsg = ":" + _client->getNickName() + " NOTICE " + target + " :" + msg;
	                    	std::string joinMsg = ":" + _client->getNickName() + " JOIN " + channels[i]->getChName();
							(*it2)->sendReply(joinMsg);
						}
	                    // _client->sendReply(joinMsg);
	                }
	                else
	                {
	                    // send message to client
	                    std::string errMsg = ERR_BADCHANNELKEY(_server->getServerName(), _client->getNickName(), channelName);
	                    _client->sendReply(errMsg);
	                }
	            }
	            else
	            {
	                // add client to channel
	                channels[i]->addUser(_client);
	                // send message to all clients in that channel
					std::vector<Client *> clients = (channels[i])->getUsers();
					std::vector<Client *>::iterator it2 = clients.begin();
					for (; it2 != clients.end(); it2++)
					{
						std::string joinMsg = ":" + _client->getNickName() + " JOIN " + channels[i]->getChName();
						(*it2)->sendReply(joinMsg);
					}
					// std::string joinMsg = ":" + _client->getNickName() + " JOIN " + (channels[i])->getChName();
					// _client->sendReply(joinMsg);
					std::string topicMsg;
					if (channels[i]->getTopic() != "SET TOPIC")
						topicMsg = RPL_TOPIC(_server->getServerName(), _client->getNickName(), channels[i]->getChName(), channels[i]->getTopic());
					else
						topicMsg = ":" + _client->getServerName() + " 331 " + _client->getNickName() + " " + _client->getNickName() + " " + channelName + " :No topic is set";
					_client->sendReply(topicMsg);
	            }
	        }
	    }
		if (flag == 0){
		    //if channel does not exist create 
		    Channel *channel = new Channel(_client,channelName);
		    // channel->addUser(_client); // don't uncomment without Ibraar authroztion !!! :) 
		    _server->channels.push_back(channel);
		    // send message to client
		    std::string joinMsg = ":" + _client->getNickName() + " JOIN " + channel->getChName();
		    _client->sendReply(joinMsg);
		}
	}
}


// check the channel mode if it is invite only don't allow the user to join unless if it was from