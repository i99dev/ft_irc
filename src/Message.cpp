/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Message.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oal-tena <oal-tena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 19:55:02 by aaljaber          #+#    #+#             */
/*   Updated: 2022/12/08 18:02:19 by oal-tena         ###   ########.fr       */
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
		// if (it->second[0] == ':')
		// {
		// 	_Prefix = it->second.substr(1);
		// 	it++;
		// }
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
		//check wildcard
		if (is_wildCard(it->second))
			split_mask(it->second);
		else
		_Parameter.push_back(it->second);
		it++;
	}

	//cout 
	std::cout << "Command: " << _Command << std::endl;
	std::cout << "Parameter: " << std::endl;
	for (size_t i = 0; i < _Parameter.size(); i++)
	{
		std::cout << _Parameter[i] << std::endl;
	}
	std::cout << "Parameter size: " << _Parameter.size() << std::endl;
	std::cout << "_____________" << std::endl;
}

ft::Message::Message(std::string msg,int owner_fd){
	this->_owner_fd = owner_fd;
	this->_msg = msg;
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




bool ft::Message::isValid(){
	return true;
}

// bool ft::Message::isCommand(){
// 	if (_Command.empty())
// 		return false;
// 	return true;
// }


bool ft::Message::isParameter(){
	if (_Parameter.empty())
		return false;
	return true;
}

/**
 * @brief Check if the  parameter is a wildcard
*/
bool ft::Message::is_wildCard(std::string const &str){
	if (str.find('*') != std::string::npos || str.find('?') != std::string::npos)
		return true;
	return false;
}

/**
 * @brief Check if the parameter match the wildcard
*/
bool ft::Message::match_wildCard(std::string const &str, std::string const &wildcard){
	if (wildcard.find('*') != std::string::npos)
	{
		if (wildcard.find('*') == 0)
		{
			if (str.find(wildcard.substr(1)) != std::string::npos)
				return true;
		}
		else if (wildcard.find('*') == wildcard.size() - 1)
		{
			if (str.find(wildcard.substr(0, wildcard.size() - 1)) != std::string::npos)
				return true;
		}
		else
		{
			if (str.find(wildcard.substr(0, wildcard.find('*'))) != std::string::npos && str.find(wildcard.substr(wildcard.find('*') + 1)) != std::string::npos)
				return true;
		}
	}
	else if (wildcard.find('?') != std::string::npos)
	{
		if (wildcard.find('?') == 0)
		{
			if (str.find(wildcard.substr(1)) != std::string::npos)
				return true;
		}
		else if (wildcard.find('?') == wildcard.size() - 1)
		{
			if (str.find(wildcard.substr(0, wildcard.size() - 1)) != std::string::npos)
				return true;
		}
		else
		{
			if (str.find(wildcard.substr(0, wildcard.find('?'))) != std::string::npos && str.find(wildcard.substr(wildcard.find('?') + 1)) != std::string::npos)
				return true;
		}
	}
	return false;
}

void	ft::Message::split_mask(std::string &str)
{
	t_mask *mask;

	mask = new t_mask;
	if (str.find_first_of('!') != std::string::npos && str.find_last_of('@') != std::string::npos)
	{
		mask->nick = str.substr(0, str.find('!'));
		mask->user = str.substr(str.find('!') + 1 , str.find('@') - 2);
		mask->host = str.substr(str.find('@') + 1);
		_masks.push_back(mask);
		return;
	}
	else if (str.find_first_of('!')  != std::string::npos && str.find_last_not_of('@') != std::string::npos)
	{
		mask->nick = str.substr(0, str.find('!'));
		mask->user = str.substr(str.find('!') + 1);
		_masks.push_back(mask);
		return;
	}
	else if (str.find_first_of('@') != std::string::npos)
	{
		mask->nick = str.substr(0, str.find('@'));
		mask->host = str.substr(str.find('@') + 1);
		_masks.push_back(mask);
		return;
	}
	else if (str.find_first_of('*') != std::string::npos || str.find_first_of('?') != std::string::npos)
	{
		mask->wildcard = str;
		_masks.push_back(mask);
		return;
	}
	else
	{
		mask->nick = str;
		_masks.push_back(mask);
		return;
	}
}

bool	ft::Message::is_mask(void)
{
	if (_masks.empty())
		return false;
	return true;
}

bool	ft::Message::match_client_mask(ft::Client *client)
{
	std::vector<t_mask *>::iterator it = _masks.begin();
	std::vector<t_mask *>::iterator ite = _masks.end();

	while (it != ite)
	{
		if ((*it)->nick != "" && (*it)->nick.size() > 1 && match_wildCard(client->getNickName(), (*it)->nick) == false)
			return false;
		if ((*it)->user != "" && (*it)->user.size() > 1 && match_wildCard(client->getUserName(), (*it)->user) == false)
			return false;
		if ((*it)->host != "" && (*it)->host.size() > 1 && match_wildCard(client->getHostName(), (*it)->host) == false)
			return false;
		if ((*it)->wildcard != "" && (*it)->wildcard.size() > 1 && !match_wildCard(client->getNickName(), (*it)->wildcard))
			return false;
		it++;
	}
	return true;
}