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
            if ((*it)->getPassword() != "")
            {
                // check if key is correct
                if ((*it)->getPassword() == channelKey)
                {
                    // add client to channel
                    (*it)->addClient(_client);
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
                (*it)->addClient(_client);
                // send message to client
                std::string joinMsg = ":" + _client->getNickName() + " JOIN :" + (*it)->getChName();
                _client->sendReply(joinMsg);
            }
        }
    }
    //if channel does not exist create 
    Channel *channel = new Channel(channelName, channelKey);
    channel->addClient(_client);
    channels.push_back(channel);
    // send message to client
    std::string joinMsg = ":" + _client->getNickName() + " JOIN :" + channel->getChName();
    _client->sendReply(joinMsg);
}
    
