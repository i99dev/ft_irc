#include "../../incl/cmd/PrivMsg.hpp"

ft::PRIVMSG::PRIVMSG(): cmd(_message->getParameter()){
    _name = "privmsg";
    _description = "Send message to a set of users/channels";
    _usage = "privmsg <receptor|channel>{,<receptor|channel>} :<texto>";
}

void	ft::PRIVMSG::execute(){
	if (check_cmd(_message->getCommand()) == false)
		return ;
	ChName = _message->getParameter()[0];
	getChannel(_server->channels);
	msg = _message->getParameter()[1];
	target->sendMsgtoChannel(_client->getMsgSend().back());    // executethe command from channel
}

bool	ft::PRIVMSG::check_cmd(std::string s){
	if (s == "PRIVMSG")
		return true;
	return false;
}

void	ft::PRIVMSG::getChannel(std::vector<ft::Channel *> channels){
	for (int i = 0; i < int(channels.size()); i++){
		if (channels[i]->getChName() == ChName){
			//send to all clinet in channel
			target = channels[i];
			return ;
		}
	}
}