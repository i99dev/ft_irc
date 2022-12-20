/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testMasks.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 06:49:45 by aaljaber          #+#    #+#             */
/*   Updated: 2022/12/21 00:58:54 by aaljaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/Mask.hpp"
#include <iostream>

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
				return mask;
			}
		}
    }
	delete mask;
	std::cout << "ignore this case .. it's not a mask" << std::endl;
	return (NULL);
}


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

ft::Mask::Mask(std::string const &str):_mask(NULL), is_WildCard(false), is_mask(false)
{
    std::string tmp = str;
    this->_mask = split_mask(tmp);
	this->_mask->is_mask = this->is_mask;
    if (str.find('*') != std::string::npos)
	{
		if (str.find_first_of('*') == str.find_last_of('*'))
			is_WildCard = true;
	}
}

ft::Mask::~Mask(void)
{
	if (_mask)
   		delete _mask;
}

t_mask	*ft::Mask::getMask(void)
{
	return (this->_mask);
}

/*
* nick!user@host
? *!*@*
? nic*!user@host
? nick!@
? !@host
*/
int main ()
{
	ft::Mask wild ("la*!@m*l");
	std::cout << "nick " << wild.getMask()->nick << std::endl;
	std::cout << "user " << wild.getMask()->user << std::endl;
	std::cout << "host " << wild.getMask()->host << std::endl;
	std::string nick = "lala";
	std::cout << "does it match " << nick << " " << wild.match_wildCard(nick, "*") << std::endl;
}