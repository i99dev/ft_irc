/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   List.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 06:56:51 by oal-tena          #+#    #+#             */
/*   Updated: 2022/12/26 17:18:40 by aaljaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/cmd/List.hpp"

ft::List::List(void)
{
	_name = "List";
	_description = "List all channels or status of specified channels.";
	_usage = "list [<channel>{,<channel>}]";
}

void    ft::List::execute(){
	if (_message->getParameter().size() > 2){
		_client->sendReply(ERR_NEEDMOREPARAMS(_server->getServerName(), _client->getNickName(), _message->getCommand()));
		return ;
	}
	_client->sendReply(RPL_LISTSTART(_server->getServerName(), _client->getNickName()));
	if (_message->getParameter().size() == 0){
		for (int i = 0; i < int(_server->channels.size()); i++){
			std::stringstream s;
			std::string ss = "";
			s << _server->channels[i]->members.size();
			s >> ss;
			_client->sendReply(RPL_LIST(_server->getServerName(), _client->getNickName(), _server->channels[i]->getChName(), ss, _server->channels[i]->getCHMode(), _server->channels[i]->getTopic()));
		}
	}
	else{
		std::vector<std::string> channels;
		std::string s;
		int i = 0;
		while(_message->getParameter()[0][i] != '\0')
		{
			if(_message->getParameter()[0][i] != ',')
			{
				s += _message->getParameter()[0][i];   // append the char array to the temp string
			}
			else{
				channels.push_back(s);
				s.clear();
			}
			i++;
	 
		}
		channels.push_back(s);
		bool ok = false;
		for (int j = 0; j < int(channels.size()); j++){
			ok = false;
			for (int c = 0; c < int(_server->channels.size()); c++){
				if (_server->channels[c]->getChName() == channels[j]){
					ok = true;
					std::stringstream s;
					std::string ss = "";
					s << _server->channels[c]->members.size();
					s >> ss;
					_client->sendReply(RPL_LIST(_server->getServerName(), _client->getNickName(), _server->channels[c]->getChName(), ss, _server->channels[c]->getCHMode(), _server->channels[c]->getTopic()));
				}
			}
			if (!ok)
				_client->sendReply(ERR_NOSUCHCHANNEL(_server->getServerName(), _client->getNickName(), channels[j]));
		}
	}
	_client->sendReply(RPL_LISTEND(_server->getServerName(), _client->getNickName()));
}
