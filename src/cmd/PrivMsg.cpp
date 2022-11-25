#include "../../incl/cmd/PrivMsg.hpp"

ft::PRIVMSG::PRIVMSG(std::vector<ft::Channel *> channels, Client *client): cmd(client->getMsgSend().back()->getCommand()), cmdCount(client->getMsgSend().back()->getCmdCount()){
	if (check_cmd(client) == false)
		return ;
	getChName(client);
	getChannel(channels);
	getMsg();
	execute(client);
}

void	ft::PRIVMSG::execute(Client *client){
	target->sendMsgtoChannel(client->getMsgSend().back());
}

bool    ft::PRIVMSG::check_cmd(ft::Client *client){
	if (client->getMsgSend().back()->getCommand()[0] == "PRIVMSG")
		return true;
	return false;
}

void	ft::PRIVMSG::getChName(Client *client){
	char *tmp;
	client->getMsgSend().back()->getCommand()[1].copy(tmp, client->getMsgSend().back()->getCommand()[1].size() - 1, 1);
	ChName = std::string(tmp);
}

void	ft::PRIVMSG::getChannel(std::vector<ft::Channel *> channels){
	for (int i = 0; i < channels.size(); i++){
		if (channels[i]->getChName() == ChName){
			target = channels[i];
			return ;
		}
	}
}

void	ft::PRIVMSG::getMsg(){
	int i = 2;
	char *tmp;

	tmp = new char[cmd[i].size() - 1];
	cmd[i].copy(tmp, cmd[i].size() - 1, 1);
	msg = std::string(tmp);
	i++;
	while (i < cmdCount){
		msg += " ";
		msg += cmd[i];
		i++;
	}
	delete[] tmp;
}