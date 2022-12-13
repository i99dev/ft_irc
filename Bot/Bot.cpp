/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bot.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isaad <isaad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 10:58:57 by oal-tena          #+#    #+#             */
/*   Updated: 2022/12/13 21:49:03 by isaad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bot.hpp"

int main(int argc, char **argv)
{
	if (argc != 3) {
		std::cerr << "Usage: " << argv[0] << " <host> <port>" << std::endl;
		exit(1);
	}
	ft::Bot bot(argv[2], argv[1]);
}

ft::Bot::Bot(std::string p, char *h){
	this->port = p;
	this->host = h;
	this->sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0) {
		std::cerr << "Error creating socket" << std::endl;
		exit(1);
	}

	// Fill in the address of the server
	struct sockaddr_in serv_addr;
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(std::stoi(this->port));
	serv_addr.sin_addr.s_addr = inet_addr(this->host);

	// Connect to the server
	if (connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
		std::cerr << "Error connecting to the server" << std::endl;
		exit(1);
	}
	doProcess();
}

void ft::Bot::sendToServer(std::string msg){
	std::string message = msg + "\n";
	if (send(this->sockfd, message.c_str(), message.size(), 0) < 0) {
		std::cerr << "Error sending message to the server" << std::endl;
	}
}

std::string ft::Bot::receiveFromServer(){
	char recv_buffer[1024] = {0};
	if (recv(sockfd, recv_buffer, sizeof(recv_buffer), 0) <= 0){
		std::cerr << "Error receiving message from the server" << std::endl;
		close(this->sockfd);
		exit(1);
	}
	return std::string(recv_buffer);
}

ft::Bot::~Bot(){
	close(this->sockfd);
}

void ft::Bot::generateNickName(){
	std::string nick = "NICK bot";
	std::string nickName = "bot";
	std::string reply = "";
	while (1){
		sendToServer(nick + "\r");
		reply = receiveFromServer();
		if (reply.find("001") != std::string::npos)
			break;
		nick += "_";
		nickName += "_";
	}
	this->_nickname = nickName;
}

void ft::Bot::getMsgRecv(int start){
	this->msgRecv = "";
	std::string tmp = "";
	while (this->msg[start] != ':' && this->msg[start])
		start++;
	if (this->msg[start] == ':'){
		start++;
		while (this->msg[start] != '\n' && this->msg[start])
		{
			this->msgRecv += this->msg[start];
			start++;
		}
	}
	for (int i = 0; i < int(this->msgRecv.size()); i++){
		tmp += tolower(this->msgRecv[i]);
	}
	this->msgRecv = tmp;
	std::cout << "____" << this->msgRecv << "____" << std::endl;
}

bool help(std::string msgRecv){
	if (msgRecv.find("help") != std::string::npos)
		return true;
	return false;
}

bool commands(std::string msgRecv){
	if ((msgRecv.find("commands") != std::string::npos && (msgRecv.find("tell") != std::string::npos || msgRecv.find("available") != std::string::npos)))
		return true;
	return false;
}

bool greeting(std::string msgRecv){
	if (msgRecv.find("hello") != std::string::npos ||
		msgRecv.find("hey") != std::string::npos ||
		msgRecv.find("hi") != std::string::npos)
		return true;
	return false;
}

bool syntaxUser(std::string msgRecv){
	if ((msgRecv.find("syntax") != std::string::npos && (msgRecv.find("user") != std::string::npos)))
		return true;
	return false;
}

bool syntaxNick(std::string msgRecv){
	if ((msgRecv.find("syntax") != std::string::npos && (msgRecv.find("nick") != std::string::npos)))
		return true;
	return false;
}

bool syntaxPing(std::string msgRecv){
	if ((msgRecv.find("syntax") != std::string::npos && (msgRecv.find("ping") != std::string::npos)))
		return true;
	return false;
}

bool syntaxQuit(std::string msgRecv){
	if ((msgRecv.find("syntax") != std::string::npos && (msgRecv.find("quit") != std::string::npos)))
		return true;
	return false;
}

bool syntaxKill(std::string msgRecv){
	if ((msgRecv.find("syntax") != std::string::npos && (msgRecv.find("kill") != std::string::npos)))
		return true;
	return false;
}

bool syntaxJoin(std::string msgRecv){
	if ((msgRecv.find("syntax") != std::string::npos && (msgRecv.find("join") != std::string::npos)))
		return true;
	return false;
}

bool syntaxPart(std::string msgRecv){
	if ((msgRecv.find("syntax") != std::string::npos && (msgRecv.find("part") != std::string::npos)))
		return true;
	return false;
}

bool syntaxPrivmsg(std::string msgRecv){
	if ((msgRecv.find("syntax") != std::string::npos && (msgRecv.find("privmsg") != std::string::npos)))
		return true;
	return false;
}

bool syntaxNotice(std::string msgRecv){
	if ((msgRecv.find("syntax") != std::string::npos && (msgRecv.find("notice") != std::string::npos)))
		return true;
	return false;
}

bool syntaxInvite(std::string msgRecv){
	if ((msgRecv.find("syntax") != std::string::npos && (msgRecv.find("invite") != std::string::npos)))
		return true;
	return false;
}

bool syntaxKick(std::string msgRecv){
	if ((msgRecv.find("syntax") != std::string::npos && (msgRecv.find("kick") != std::string::npos)))
		return true;
	return false;
}

bool syntaxTopic(std::string msgRecv){
	if ((msgRecv.find("syntax") != std::string::npos && (msgRecv.find("topic") != std::string::npos)))
		return true;
	return false;
}

bool syntaxMode(std::string msgRecv){
	if ((msgRecv.find("syntax") != std::string::npos && (msgRecv.find("mode") != std::string::npos)))
		return true;
	return false;
}

bool syntaxWhois(std::string msgRecv){
	if ((msgRecv.find("syntax") != std::string::npos && (msgRecv.find("whois") != std::string::npos)))
		return true;
	return false;
}

bool syntaxList(std::string msgRecv){
	if ((msgRecv.find("syntax") != std::string::npos && (msgRecv.find("list") != std::string::npos)))
		return true;
	return false;
}

bool syntaxJoke(std::string msgRecv){
	if (msgRecv.find("joke") != std::string::npos)
		return true;
	return false;
}

void ft::Bot::reply(){
	this->toSend = "";
	this->toSend += format;
	if (greeting(this->msgRecv))
		this->toSend += WLCM;
	if (help(this->msgRecv))
		this->toSend += HELP(this->format);
	if (commands(this->msgRecv))
		this->toSend += CMDLIST(this->format);
	while (1){
		int i = 0;
		if(syntaxUser(this->msgRecv) && i < 3){
			this->toSend += USER(this->format);
			i++;
		}
		if (syntaxNick(this->msgRecv) && i < 3){
			this->toSend += NICK(this->format);
			i++;
		}
		if (syntaxPing(this->msgRecv) && i < 3){
			this->toSend += PING(this->format);
			i++;
		}
		if (syntaxQuit(this->msgRecv) && i < 3){
			this->toSend += QUIT(this->format);
			i++;
		}
		if (syntaxKill(this->msgRecv) && i < 3){
			this->toSend += KILL(this->format);
			i++;
		}
		if (syntaxJoin(this->msgRecv) && i < 3){
			this->toSend += JOIN(this->format);
			i++;
		}
		if (syntaxPart(this->msgRecv) && i < 3){
			this->toSend += PART(this->format);
			i++;
		}
		if (syntaxPrivmsg(this->msgRecv) && i < 3){
			this->toSend += PRIVMSG(this->format);
			i++;
		}
		if (syntaxNotice(this->msgRecv) && i < 3){
			this->toSend += NOTICE(this->format);
			i++;
		}
		if (syntaxInvite(this->msgRecv) && i < 3){
			this->toSend += INVITE(this->format);
			i++;
		}
		if (syntaxKick(this->msgRecv) && i < 3){
			this->toSend += KICK(this->format);
			i++;
		}
		if (syntaxTopic(this->msgRecv) && i < 3){
			this->toSend += TOPIC(this->format);
			i++;
		}
		if (syntaxMode(this->msgRecv) && i < 3){
			this->toSend += MODE(this->format);
			i++;
		}
		if (syntaxWhois(this->msgRecv) && i < 3){
			this->toSend += WHOIS(this->format);
			i++;
		}
		if (syntaxList(this->msgRecv) && i < 3){
			this->toSend += LIST(this->format);
			i++;
		}
		break ;
	}
	if (syntaxJoke(this->msgRecv))
		this->toSend += getJoke();
	this->toSend += "\r";
	sendToServer(this->toSend);
}

void ft::Bot::getSender(){
	std::string checker = "";
	int i = 0;
	int j = 1;
	this->sender = "";
	checker += this->msg[0];
	if (this->msg[0] == ':'){
		checker += this->msg[1];
		j++;
		i++;
	}
	while (checker[i] != ' ' && checker[i] != '!' && checker[i])
	{
		this->sender += this->msg[i];
		checker += this->msg[j];
		i++;
		j++;
	}
	std::cout << "____" << this->sender << "____" << std::endl;
}

void ft::Bot::loop(){
	int i = 0;
	while (1){
		this->msg = receiveFromServer();
		if (this->msg.size() > 1 && ((i = this->msg.find("NOTICE") != std::string::npos) || (i = this->msg.find("PRIVMSG") != std::string::npos))){
			getSender();
			if (this->msg.find("NOTICE") != std::string::npos)
				this->format = "NOTICE " + this->sender + " :";
			else
				this->format = "PRIVMSG " + this->sender + " :";
			getMsgRecv(i);
			reply();
		}
		std::cout << this->msg << std::endl;
	}
}

void ft::Bot::doProcess(){
	this->msg = "";
	this->msgRecv = "";
	sendToServer("CAP LS\r");
	generateNickName();
	sendToServer("USER " + this->_nickname + " " + this->_nickname + " 127.0.0.1 :bot\r");
	loop();
}

std::string ft::Bot::getJoke(){
	std::srand(time(0));
	return this->jokes[std::rand() % 105];
}