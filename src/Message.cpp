/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Message.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isaad <isaad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 19:55:02 by aaljaber          #+#    #+#             */
/*   Updated: 2022/11/28 13:48:49 by isaad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/Message.hpp"
#include "../incl/cmd/PrivMsg.hpp"

/******************* GETTERS *******************/
/**
 * @brief Parse the message received from the client
 *
*/
void ft::Message::parseMessage(std::string const &msg)
{
	int	i = 0;
	int	words = 0;
	int	flag = 1;

	std::cout << "Parsing message" << std::endl;
	std::cout << "________" << msg << "________" << std::endl;

	// count how many words we have received
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

	// final is the variable to store the words
	char *final;

	i = 0; // index
	int j = 0; // count the length of each word
	int counter = 0; // count the number of words done
	int start = 0; // start index of each word

	// copying the parameters word by word
	while (counter < words){
		j = 0;
		while ((msg[i] == ' ' || msg[i] == '\n' || msg[i] == 13) && msg[i])
			i++;
		if ((msg[i] != ' ' && msg[i] != '\n'))
			start = i;
		while ((msg[i] != ' ' && msg[i] != '\n')){
			i++;
			j++;
		}
		if (j >= 1){
			final = new char[j + 1];
			msg.copy(final, j, start);
			final[j] = 0;
			_Command.push_back(std::string(final));
			delete[] final;
			while ((msg[i] == ' ' || msg[i] == '\n'))
				i++;
			counter++;
		}
	}

	for (int i = 0; i < words; i++)
		std::cout << "Command: " << _Command[i] << std::endl;
}

ft::Message::Message(std::string msg,int owner_fd):_msg(msg),_owner_fd(owner_fd){
	parseMessage(msg);
}

ft::Message::~Message(){
}

int ft::Message::gerOwnerFd(){
	return _owner_fd;
}

std::vector<std::string> ft::Message::getCommand(){
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


