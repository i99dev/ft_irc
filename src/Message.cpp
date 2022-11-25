/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Message.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isaad <isaad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 19:55:02 by aaljaber          #+#    #+#             */
/*   Updated: 2022/11/25 20:56:38 by isaad            ###   ########.fr       */
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
	char **final = new char*[words + 1];

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
			final[counter] = new char[j + 1];
			msg.copy(final[counter], j, start);
			final[counter][j] = 0;
			while ((msg[i] == ' ' || msg[i] == '\n'))
				i++;
			counter++;
		}
	}
	final[counter] = 0;
	
	// copying one by one is required
	_Command = new std::string[words + 1];
	for (int i = 0; i < words; i++)
		_Command[i] = std::string(final[i]);

	//freeing the double array
	for (int i = 0; i < words; i++)
		delete[] final[i];
	delete[] final;

	for (int i = 0; i < words; i++)
		std::cout << "Command: " << _Command[i] << std::endl;
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


