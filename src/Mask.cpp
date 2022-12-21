/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mask.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 13:40:30 by oal-tena          #+#    #+#             */
/*   Updated: 2022/12/20 09:12:12 by aaljaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/Mask.hpp"
#include "../incl/Client.hpp"

t_mask	*ft::Mask::getMask(void)
{
	return (this->_mask);
}

/**
 * @brief Check if the parameter match the Mask
 */
bool ft::Mask::match_wildCard(std::string const &str, std::string const &Mask)
{
    if (Mask.find('*') != std::string::npos)
    {
        if (Mask.find('*') == 0)
        {
            if (str.find(Mask.substr(1)) != std::string::npos)
                return true;
        }
        else if (Mask.find('*') == Mask.size() - 1)
        {
            if (str.find(Mask.substr(0, Mask.size() - 1)) != std::string::npos)
                return true;
        }
        else
        {
            if (str.find(Mask.substr(0, Mask.find('*'))) != std::string::npos && str.find(Mask.substr(Mask.find('*') + 1)) != std::string::npos)
                return true;
        }
    }
	else if (str == Mask)
		return (true);
    return false;
}

t_mask *split_mask(std::string &str)
{
	t_mask *mask = new t_mask;
	mask->is_mask = false;
    if (str.find('!') != std::string::npos && str.find('@') != std::string::npos)
    {
		if (str.find_first_of('!') == str.find_last_of('!') && str.find_first_of('@') && str.find_last_of('@'))
		{
			if (str.find('!') < str.find('@'))
			{
				mask->nick = str.substr(0, str.find('!'));
				if (str[str.find('!') + 1] != '@')
					mask->user = str.substr(str.find('!') + 1, str.find('@') - (str.find('!') + 1));
				mask->host = str.substr(str.find('@') + 1);
				mask->is_mask = true;
				std::cout << "this case is a mask" << std::endl;
				return mask;
			}
		}
    }
	delete mask;
	std::cout << "ignore this case .. it's not a mask" << std::endl;
	return (NULL);
}

bool ft::Mask::match_client_mask(ft::Client *client)
{
    if (_mask->nick != "" && _mask->nick.size() > 1 && match_wildCard(client->getNickName(), _mask->nick) == false)
        return false;
    if (_mask->user != "" && _mask->user.size() > 1 && match_wildCard(client->getUserName(), _mask->user) == false)
        return false;
    if (_mask->host != "" && _mask->host.size() > 1 && match_wildCard(client->getHostName(), _mask->host) == false)
        return false;
    return true;
}

ft::Mask::Mask(std::string const &str):_mask(NULL), is_WildCard(false)
{
    std::string tmp = str;
    this->_mask = split_mask(tmp);
	this->is_mask = this->_mask->is_mask;
	std::cout << "is mask? " << this->is_mask << std::endl;
    if (str.find('*') != std::string::npos)
	{
		if (str.find_first_of('*') == str.find_last_of('*'))
			is_WildCard = true;
	}
}

bool	ft::Mask::is_SameMask(t_mask *mask)
{
	if (this->_mask->nick == mask->nick)
	{
		if (this->_mask->user == mask->user)
		{
			if (this->_mask->host == mask->host)
				return (true);
		}
	}
	return (false);
}

ft::Mask::~Mask(void)
{
	if (_mask)
   		delete _mask;
}
