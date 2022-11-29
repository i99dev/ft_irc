#include "../../incl/cmd/Join.hpp"

ft::Join::Join(void)
{
    _name = "Join";
    _description = "Join a channel";
    _usage = "/join <channel> [key]";
}

void ft::Join::execute()
{
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
		cmd.copy(s, size - 1, start + 1);
		s[size] = 0;
		chName.push_back(std::string(s));
		delete [] s;
		j++;
	}
	j = 0;
	start = 0;
	size = 0;
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


    // get channel name from message
    std::string channelName = _message->getParameter()[0];
    // get channel key from message
    std::string channelKey = "";
    // if ( _message->getParameter()[1] != "")
    // {
    //     std::string channelKey = _message->getParameter()[1];
    // }
    // check if channel exists
    std::vector<Channel *>::iterator it;
    for (it = channels.begin(); it != channels.end(); it++)
    {
        if ((*it)->getChName() == channelName)
        {
            // check if channel has a key
            if ((*it)->getpassword() != "")
            {
                // check if key is correct
                if ((*it)->getpassword() == channelKey)
                {
                    // add client to channel
                    (*it)->addUser(_client);
                    // send message to client
                    std::string joinMsg = ":" + _client->getNickName() + " JOIN :" + (*it)->getChName();
                    _client->sendReply(joinMsg);
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
                (*it)->addUser(_client);
                // send message to client
                std::string joinMsg = ":" + _client->getNickName() + " JOIN :" + (*it)->getChName();
                _client->sendReply(joinMsg);
            }
        }
    }
    //if channel does not exist create 
    Channel *channel = new Channel(_client,channelName);
    // channel->addUser(_client); // don't uncomment without Ibraar authroztion !!! :) 
    _server->channels.push_back(channel);
    // send message to client
    std::string joinMsg = ":" + _client->getNickName() + " JOIN :" + channel->getChName();
    _client->sendReply(joinMsg);
}
    
