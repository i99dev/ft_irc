/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bot.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isaad <isaad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 10:58:57 by oal-tena          #+#    #+#             */
/*   Updated: 2022/12/13 00:05:14 by isaad            ###   ########.fr       */
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
	recv(sockfd, recv_buffer, sizeof(recv_buffer), 0);
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

void ft::Bot::loop(){
	std::string reply = "";
	while (1){
		reply = receiveFromServer();
		std::cout << reply << std::endl;
		if (reply.find("PING") != std::string::npos){
			sendToServer("PONG " + reply.substr(5) + "\r");
		}
	}
}

void ft::Bot::doProcess(){
	sendToServer("CAP LS\r");
	generateNickName();
	sendToServer("USER " + this->_nickname + " " + this->_nickname + " 127.0.0.1 :bot\r");
	loop();
}