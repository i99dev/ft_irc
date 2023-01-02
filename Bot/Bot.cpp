/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bot.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isaad <isaad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 10:58:57 by oal-tena          #+#    #+#             */
/*   Updated: 2023/01/01 15:07:34 by isaad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

bool closeServer = false;
#include "Bot.hpp"
#include "msgAdd.cpp"
#include <signal.h>
#include <csignal>
#include <poll.h>

int main(int argc, char **argv)
{
	if (argc != 5) {
		std::cerr << "Usage: " << argv[0] << " <host> <port> <pass> <nick>" << std::endl;
		exit(1);
	}
	for (size_t i = 0; i < strlen(argv[2]); i++)
    {
        if (!isdigit(argv[2][i]))
        {
            std::cout << "Port must be a number" << std::endl;
            return (EXIT_FAILURE);
        }
    }
	ft::Bot bot(argv[2], argv[1], argv[3], argv[4]);
}

ft::Bot::Bot(std::string p, char *h, std::string pass, std::string nick){
	this->port = p;
	this->host = h;
	this->pass = pass;
	this->nick = nick;
	this->sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0) {
		std::cerr << "Error creating socket" << std::endl;
		exit(1);
	}

	// Fill in the address of the server
	struct sockaddr_in serv_addr;
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(6667);
	serv_addr.sin_addr.s_addr = inet_addr(this->host);

	// Connect to the server
	if (connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
		std::cerr << "Error connecting to the server" << std::endl;
		exit(1);
	}
	doProcess();
}

void ft::Bot::sendToServer(std::string msg){
	std::string message = msg;
	if (send(this->sockfd, message.c_str(), message.size(), 0) < 0) {
		std::cerr << "Error sending message to the server" << std::endl;
	}
}

std::string ft::Bot::receiveFromServer(){
	char recv_buffer[1024] = {0};
	if (recv(sockfd, recv_buffer, sizeof(recv_buffer), 0) <= 0){
		std::cerr << "Error receiving message from the server" << std::endl;
		close(this->sockfd);
		return "error";
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
		sendToServer(nick + "\r\n");
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
}

bool syntaxJoke(std::string &msgRecv){
	if (msgRecv.find("joke") != std::string::npos)
		return true;
	return false;
}

void ft::Bot::reply(){
	int j = 0;
	this->toSend = "";
	std::string tmp = "";
	for (int i = 0; i < int(ctrl.size()); i++){
		tmp = this->toSend;
		if (j < 5)
			this->toSend = ctrl[i](this->msgRecv, this->toSend, this->sender);
		if (tmp != this->toSend){
			this->toSend += "\r\n";
			j++;
		}
	}
	tmp = "";
	for (int i = 0; i < int(func.size()); i++){
		tmp = this->toSend;
		if (j < 5)
			this->toSend = func[i](this->msgRecv, this->toSend, this->format);
		if (tmp != this->toSend){
			this->toSend += "\r\n";
			j++;
		}
	}
	if (syntaxJoke(this->msgRecv)){
		this->toSend += getJoke();
		j++;
	}
	if (j == 0)
		this->toSend += DEFAULT(this->format) + "\r\n";
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
}

void ft::Bot::header(int i, std::string s){
	std::string msg = "";
	while (s[i] != ':' && s[i])
		i++;
	while (s[++i])
		msg += s[i];
	std::cout << "\033[0;32m" << msg << "\033[0;00m" << std::endl;
}


void sig_handler(int signo)
{
	(void)signo;
    if (signo == SIGINT)
    {
        std::cout << "NOT SAFE to close it through ctrl c\nCLOSE the server instead" << std::endl;
        closeServer = true;
		exit(0);
    }
}

void ft::Bot::loop(){
	int i = 0;
	while (!closeServer){

		if ((this->msg = receiveFromServer()) == "error")
			return ;
		if (this->msg.size() > 1 && ((i = this->msg.find("NOTICE") != std::string::npos) || (i = this->msg.find("PRIVMSG") != std::string::npos))){
			getSender();
			if (this->msg.find("NOTICE") != std::string::npos)
				this->format = "NOTICE " + this->sender + " :";
			else
				this->format = "PRIVMSG " + this->sender + " :";
			getMsgRecv(i);
			reply();
		}
		if ((this->msg.find(" 004 ") != std::string::npos) || (this->msg.find(" 003 ") != std::string::npos) || (this->msg.find(" 002 ") != std::string::npos)){
			std::string s = "";
			std::string tmp = this->msg;
			i = 0;
			while(tmp[i] != '\0')
			{
				if(tmp[i] != '\n')
				{
					s += tmp[i];
				}
				else{
					int j = 0;
					if ((j = s.find(" 004 ") != std::string::npos) || (j = s.find(" 003 ") != std::string::npos) || (j = s.find(" 002 ") != std::string::npos))
						header(j, s);
					s.clear();
				}
				i++;
			}
		}
	}
	std::raise(SIGINT);
}

void ft::Bot::initCtrl(){
	ctrl.push_back(create);
	ctrl.push_back(invite);
	ctrl.push_back(shout);
}

void ft::Bot::initFunc(){
	func.push_back(help);
	func.push_back(ehelp);
	func.push_back(commands);
	func.push_back(greeting);
	func.push_back(syntaxUser);
	func.push_back(syntaxNick);
	func.push_back(syntaxPing);
	func.push_back(syntaxQuit);
	func.push_back(syntaxKill);
	func.push_back(syntaxJoin);
	func.push_back(syntaxPart);
	func.push_back(syntaxPrivmsg);
	func.push_back(syntaxNotice);
	func.push_back(syntaxInvite);
	func.push_back(syntaxKick);
	func.push_back(syntaxTopic);
	func.push_back(syntaxMode);
	func.push_back(syntaxWhois);
	func.push_back(syntaxList);
}

void ft::Bot::doProcess(){
	this->msg = "";
	this->msgRecv = "";
	initFunc();
	initCtrl();
	sendToServer("CAP LS\r\n");
	sendToServer("PASS " + this->pass + "\r\n");
	sendToServer("NICK " + this->nick + "\r\n");
	// generateNickName();
	sendToServer("USER " + this->nick + " " + this->nick + " 127.0.0.1 :bot\r\n");
	loop();
}

std::string ft::Bot::getJoke(){
	std::srand(time(0));
	return this->format + this->jokes[std::rand() % 105] + "\r\n";
}