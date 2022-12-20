/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testMasks.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 06:49:45 by aaljaber          #+#    #+#             */
/*   Updated: 2022/12/20 07:14:18 by aaljaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/WildCard.hpp"
#include <iostream>


void ft::WildCard::split_mask(std::string &str)
{
    _masks = new t_mask;
    if (str.find('!') != std::string::npos && str.find('@') != std::string::npos)
    {
		if (str.find_first_of('!') == str.find_last_of('!') && str.find_first_of('@') && str.find_last_of('@'))
		{
			if (str.find('!') < str.find('@'))
			{
				std::cout << "1 here" << std::endl;
				std::cout << "first of @ " << str.find_first_of('@') << str.find('@') << std::endl;
				_masks->nick = str.substr(0, str.find('!'));
				if (str[str.find('!') + 1] != '@')
					_masks->user = str.substr(str.find('!') + 1, str.find('@') - (str.find('!') + 1));
				_masks->host = str.substr(str.find('@') + 1);
				return ;
			}
		}
    }
    // else if (str.find('!') != std::string::npos && str.find_last_not_of('@') != std::string::npos)
    // {
	// 	std::cout << "2 here" << std::endl;
    //     _masks->nick = str.substr(0, str.find('!'));
    //     _masks->user = str.substr(str.find('!') + 1);
    //     return;
    // }
    // else if (str.find_first_of('@') != std::string::npos)
    // {
	// 	std::cout << "3 here" << std::endl;
    //     _masks->nick = str.substr(0, str.find('@'));
    //     _masks->host = str.substr(str.find('@') + 1);
    //     return;
    // }
    // else if (str.find_first_of('*') != std::string::npos)
    // {
	// 	std::cout << "4 here" << std::endl;
    //     _masks->wildcard = str;
    //     return;
    // }
    // else
    // {
	// 	std::cout << "5 here" << std::endl;
    //     _masks->nick = str;
    //     return;
    // }
	std::cout << "ignore this case .. it's not a mask" << std::endl;
}

ft::WildCard::WildCard(std::string const &str)
{
    std::string tmp = str;
    // check if the parameter is a mask
    // if (is_wildCard(str))
    // {
        split_mask(tmp);
    // }
}

ft::WildCard::~WildCard(void)
{
    delete _masks;
}

t_mask	*ft::WildCard::getMask(void)
{
	return (this->_masks);
}

int main ()
{
	ft::WildCard wild ("m*!m@*l");
	std::cout << "nick " << wild.getMask()->nick << std::endl;
	std::cout << "user " << wild.getMask()->user << std::endl;
	std::cout << "host " << wild.getMask()->host << std::endl;
}