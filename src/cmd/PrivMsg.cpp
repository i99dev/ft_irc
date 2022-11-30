#include "../../incl/cmd/PrivMsg.hpp"
#include <iterator>
ft::Privmsg::Privmsg(){
    _name = "privmsg";
    _description = "Send message to a set of users/channels";
    _usage = "privmsg <receptor|channel>{,<receptor|channel>} :<texto>";
}

void	ft::Privmsg::execute(){
	std::string channelName = _message->getParameter()[0];
	std::string msg = _message->getParameter()[1];
	std::vector<Channel *>::iterator it =_server->channels.begin();
	for (; it != _server->channels.end(); it++)
	{
		if ((*it)->getChName() == channelName)
		{
			std::vector<Client *> clients = (*it)->getMe();
			std::vector<Client *>::iterator it2 = clients.begin();
			for (; it2 != clients.end(); it2++)
			{
				if ((*it2)->fd != _client->fd)
				{
					std::string reply = ":" + _client->getNickName() + "!" + _client->getUserName() + "@" + _client->getIp() + " PRIVMSG " + channelName + " :" + msg;;
					(*it2)->sendReply(reply);
				}
			}
		}
	}
}


