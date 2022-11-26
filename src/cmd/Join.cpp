#include "../../incl/cmd/Join.hpp"

ft::Join::Join(ft::Client *client, std::vector<ft::Channel *> &channels): cmd(client->getMsgSend().back()->getCommand()), Count(1){
	if (check_cmd(client) == false)
		return ;
	getChannelName(client);
}

bool	ft::Join::check_cmd(ft::Client *client){
	if (client->getMsgSend().back()->getCommand()[0] == "JOIN")
		return true;
	return false;
}

void	ft::Join::getChannelName(ft::Client *client){
	char *s;

	int j = 0;
	int size = 0;
	int start = 0;
	for(int i = 0; i < cmd[1].size(); i++){
		if (cmd[1][i] == ',')
			this->Count++;
	}
	std::cout << "count: " << this->Count << std::endl;
	if (this->Count > 1){
		this->channels = new std::string[this->Count];
		for(int i = 0; i < this->Count; i++){
			size = 0;
			if (cmd[1][j] != ',' && cmd[1][j])
				start = j;
			while(j < cmd[1].size()){
				if (cmd[1][j] == ',')
					break ;
				j++;
				size++;
			}
			s = new char[size + 1];
			cmd[1].copy(s, size - 1, start + 1);
			s[size] = 0;
			this->channels[i] = std::string(s);
			delete [] s;
			j++;
		}
	}
	else{
		channel = cmd[1];
		password = cmd[2];
		return ;
	}
	j = 0;
	start = 0;
	size = 0;
	if (this->Count > 1 && cmd[2].empty()){
		this->passwords = new std::string[this->Count];
		for(int i = 0; i < this->Count; i++){
			size = 0;
			if (cmd[2][j] != ',' && cmd[2][j])
				start = j;
			while(j < cmd[2].size()){
				if (cmd[2][j] == ',')
					break ;
				j++;
				size++;
			}
			s = new char[size + 1];
			cmd[2].copy(s, size, start);
			s[size] = 0;
			this->passwords[i] = std::string(s);
			delete [] s;
			j++;
		}
	}
}

bool	ft::Join::check_exist(std::vector<ft::Channel *> channels){
	for (int i = 0; i < channels.size(); i++){
		if (channels[i]->getChName().compare(this->channel) == 0)
			return true;
	}
	return false;
}

ft::Join::~Join(){}