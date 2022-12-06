#include "../../incl/cmd/PrivMsg.hpp"
#include <iterator>
ft::Privmsg::Privmsg(){
    _name = "privmsg";
    _description = "Send message to a set of users/channels";
    _usage = "privmsg <receptor|channel>{,<receptor|channel>} :<texto>";
}

void	ft::Privmsg::execute(){
	if (_message->getMask().size() > 0)
	{
		//wildcard
		std::cout << "wildcard" << std::endl;
		std::vector<Client *>::iterator it = _server->clients.begin();
		for (; it != _server->clients.end(); it++)
		{
			if (_message->match_wildCard((*it)->getNickName().c_str()))
			{
				//debug
				if ((*it)->fd == _client->fd)
					continue;
				std::cout << "match:"  << (*it)->getNickName() << std::endl;
				std::string reply = ":" + _client->getNickName() + "!" + _client->getUserName() + "@" + _client->getIp() + " PRIVMSG " + _message->getMask() + " :" + _message->getParameter()[0];
				(*it)->sendReply(reply);
			}
		}
	}
	else
	{
		//channel
		std::string channelName = _message->getParameter()[0];
		std::string msg = _message->getParameter()[1];
		std::vector<Channel *>::iterator it =_server->channels.begin();
		for (; it != _server->channels.end(); it++)
		{
			if ((*it)->getChName() == channelName)
			{
				std::vector<Client *> clients = (*it)->getUsers();
				std::vector<Client *>::iterator it2 = clients.begin();
				for (; it2 != clients.end(); it2++)
				{
					if ((*it2)->fd != _client->fd)
					{
						std::string reply = ":" + _client->getNickName() + "!" + _client->getUserName() + "@" + _client->getIp() + " PRIVMSG " + channelName + " :" + msg;
						(*it2)->sendReply(reply);
						return;
					}
				}
			}
		}
		//user to user
		std::vector<Client *>::iterator it3 = _server->clients.begin();
		for (; it3 != _server->clients.end(); it3++)
		{
			if ((*it3)->getNickName() == channelName)
			{
				std::string reply = ":" + _client->getNickName() + "!" + _client->getUserName() + "@" + _client->getIp() + " PRIVMSG " + channelName + " :" + msg;
				(*it3)->sendReply(reply);
				return;
			}
		}
	}
}


