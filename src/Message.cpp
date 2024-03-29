/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Message.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 19:55:02 by aaljaber          #+#    #+#             */
/*   Updated: 2023/01/03 06:19:46 by aaljaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/Message.hpp"
#include "../incl/cmd/PrivMsg.hpp"



static std::map<size_t, std::string> tokenize(std::string const &str, const char delim)
{
	size_t                        start;
	size_t                        end = 0;
	size_t                        occurrences = 0;
	std::map<size_t, std::string> ret;

	while ((start = str.find_first_not_of(delim, end)) != std::string::npos)
	{
		end = str.find(delim, start);
		ret[occurrences] = str.substr(start, end - start);
		occurrences++;
	}
	return ret;
}
/******************* GETTERS *******************/
/**
 * @brief Parse the message received from the client
 *
*/
void ft::Message::parseMessage(std::string const &msg)
{
	std::map<size_t, std::string> tokens = tokenize(msg, ' ');
	std::map<size_t, std::string>::iterator it = tokens.begin();
	std::map<size_t, std::string>::iterator ite = tokens.end();
	std::string tmp;

	
	if (it->first == 0)
	{
		_Command = it->second;
		it++;
	}
	while (it != ite)
	{
		if (it->second[0] == ':')
		{
			tmp = it->second.substr(1);
			it++;
			while (it != ite)
			{
				tmp += " " + it->second;
				it++;
			}
			_Parameter.push_back(tmp);
			break;
		}
		//check Mask
		_Parameter.push_back(it->second);
		it++;
	}

	//cout 
	std::cout << BYEL << "_____________" << DEFCOLO  << std::endl;
	std::cout << BBLU << "Command: " << DEFCOLO << _Command << std::endl;
	std::cout << BBLU << "Parameter: " << DEFCOLO << std::endl;
	for (size_t i = 0; i < _Parameter.size(); i++)
		std::cout << _Parameter[i] << std::endl;
	std::cout << BYEL << "_____________" << DEFCOLO << std::endl;
}

ft::Message::Message(std::string msg,int owner_fd)
{
	this->_owner_fd = owner_fd;
	this->_msg = msg;
	if (msg.size() > 0)
		parseMessage(msg);
}

ft::Message::~Message(){
}

int ft::Message::gerOwnerFd(){
	return _owner_fd;
}

std::string ft::Message::getCommand(){
	return _Command;
}

std::vector<std::string> ft::Message::getParameter(){
	return _Parameter;
}

std::string	ft::Message::getmsg()
{
	return (_msg);	
}


bool ft::Message::isValid(){
	return true;
}

bool ft::Message::isParameter(){
	if (_Parameter.empty())
		return false;
	return true;
}

