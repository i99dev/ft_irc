/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Message.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isaad <isaad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 19:55:02 by aaljaber          #+#    #+#             */
/*   Updated: 2022/11/25 18:17:30 by isaad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/Message.hpp"

/******************* GETTERS *******************/
/**
 * @brief Parse the message received from the client
 * 
*/
void ft::Message::parseMessage(std::string const &msg)
{
	char *test = new char[4];
	int	i = 0;
	int	words = 0;
	int	flag = 1;

	std::cout << "Parsing message" << std::endl;
	std::cout << "________" << msg << "________" << std::endl;

	msg.copy(test, 4);

	while (msg[i])
	{
		if (msg[i] == ' ' && msg[i] != '\n' && !flag)
			flag = 1;
		else if (msg[i] != ' ' && msg[i] != '\n' && flag)
		{
			words++;
			flag = 0;
		}
		i++;
	}

	std::cout << words << std::endl;

	// static int flag2;

	// char **final = new char*[words];
	// if (std::string(test) == "JOIN"){ //|| flag2 == 0){
	// 	delete[] final;
		char **final = new char*[words + 1];
	// }

	i = 0;
	int j = 0;
	int counter = 0;
	int start = 0;

	if (std::string(test) == "JOIN"){
		// flag2 = 1;
		while (counter < words){
			j = 0;
			while (msg[i] == ' ' ||	msg[i] == '\n')
				i++;
			if (msg[i] != ' ' && msg[i] != '\n')
				start = i;
			while (msg[i] != ' ' && msg[i] != '\n'){
				i++;
				j++;
			}
			final[counter] = new char[j + 1];
			msg.copy(final[counter], j, start);
			final[counter][j] = 0;
			while (msg[i] == ' ' ||	msg[i] == '\n')
				i++;
			counter++;
		}
		final[counter] = 0;
	}
	else{
		while (counter < words){
			while (msg[i] == ' ' ||	msg[i] == '\n')
				i++;
			j = 0;
			if (msg[i] != ' ' && msg[i] != '\n')
				start = i;
			while (msg[i] != ' ' && msg[i] != '\n'){
				i++;
				j++;
			}
			final[counter] = new char[j + 1];
			msg.copy(final[counter], j, start);
			final[counter][j] = 0;
			while (msg[i] == ' ' ||	msg[i] == '\n')
				i++;
			counter++;
			// if (counter == 1 ){//&& flag2){
			// 	while (msg[i] != ' ' && msg[i] != '\n'){
			// 		i++;}
			// 	// counter++;
			// }
		}
		final[counter] = 0;
	}
	// std::cout << (std::string)final[0] << std::endl;


		// for (int i = 0; i < counter; i++)
		// 	std::cout << final[i] << std::endl;


		// for (int i = 0; i < words; i++)
		// 	delete[] final[i];
		// delete[] final;
	delete[] test;
	// std::string::size_type pos = 0;

	// if (msg[0] == ':')
	// {
	//     pos = msg.find(' ');
	//     _Prefix = msg.substr(1, pos - 1);
	//     pos++;
	// }
	// std::string::size_type pos2 = msg.find(' ', pos);
	// _Command = msg.substr(pos, pos2 - pos);
	// pos = pos2 + 1;
	// if (msg[pos] == ':')
	// {
	//     _Trailing = msg.substr(pos + 1);
	// }
	// else
	// {
	//     pos2 = msg.find(' ', pos);
	//     _Parameter = msg.substr(pos, pos2 - pos);
	//     pos = pos2 + 1;
	//     _Trailing = msg.substr(pos);
	// }
	// //get channel name from parameter
	// if (_Command == "JOIN" || _Command == "PART" || _Command == "PRIVMSG")
	// {
	// 	pos = _Parameter.find('#');
	// 	_channel = _Parameter.substr(pos);
	// }

	
	// time_t now = time(0);
	// _time = now;

	// std::cout << "----------------" << std::endl;
	// std::cout << "Command: " << _Command << std::endl;
	// std::cout << "Prefix: " << _Prefix << std::endl;
	// std::cout << "Params: " << _Parameter << std::endl;
	// std::cout << "Trailing: " << _Trailing << std::endl;
	// std::cout << "Channel: " << _channel << std::endl;
	// std::cout << "Time: " << ctime(&_time) << std::endl;
	// std::cout << "----------------" << std::endl;

	_Command = (std::string*)(final);

	//execute from here
	//this->executeCommand(command, params, trailing, i); // exmaple of command
}

ft::Message::Message(std::string msg,int owner_fd):_msg(msg),_owner_fd(owner_fd){
	parseMessage(msg);
}

ft::Message::~Message(){
	delete[] _Command;
}

int ft::Message::gerOwnerFd(){
	return _owner_fd;
}

std::string *ft::Message::getCommand(){
	return _Command;
}

std::string ft::Message::getParameter(){
	return _Parameter;
}

std::string ft::Message::getPrefix(){
	return _Prefix;
}

std::string ft::Message::getTrailing(){
	return _Trailing;
}

bool ft::Message::isValid(){
	return true;
}

// bool ft::Message::isCommand(){
// 	if (_Command.empty())
// 		return false;
// 	return true;
// }

bool ft::Message::isPrefix(){
	if (_Prefix.empty())
		return false;
	return true;
}

bool ft::Message::isParameter(){
	if (_Parameter.empty())
		return false;
	return true;
}

bool ft::Message::isTrailing(){
	if (_Trailing.empty())
		return false;
	return true;
}


