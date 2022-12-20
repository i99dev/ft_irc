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
	return (this->_masks);
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

void ft::Mask::split_mask(std::string &str)
{
    _masks = new t_mask;
    if (str.find('!') != std::string::npos && str.find('@') != std::string::npos)
    {
		if (str.find_first_of('!') == str.find_last_of('!') && str.find_first_of('@') && str.find_last_of('@'))
		{
			if (str.find('!') < str.find('@'))
			{
				_masks->nick = str.substr(0, str.find('!'));
				if (str[str.find('!') + 1] != '@')
					_masks->user = str.substr(str.find('!') + 1, str.find('@') - (str.find('!') + 1));
				_masks->host = str.substr(str.find('@') + 1);
				is_mask = true;
				return ;
			}
		}
    }
	std::cout << "ignore this case .. it's not a mask" << std::endl;
}

bool ft::Mask::match_client_mask(ft::Client *client)
{
    if (_masks->nick != "" && _masks->nick.size() > 1 && match_wildCard(client->getNickName(), _masks->nick) == false)
        return false;
    if (_masks->user != "" && _masks->user.size() > 1 && match_wildCard(client->getUserName(), _masks->user) == false)
        return false;
    if (_masks->host != "" && _masks->host.size() > 1 && match_wildCard(client->getHostName(), _masks->host) == false)
        return false;
    return true;
}

ft::Mask::Mask(std::string const &str): is_WildCard(false), is_mask(false)
{
    std::string tmp = str;
    split_mask(tmp);
    if (str.find('*') != std::string::npos)
	{
		if (str.find_first_of('*') == str.find_last_of('*'))
			is_WildCard = true;
	}
}

ft::Mask::~Mask(void)
{
    delete _masks;
}
