/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WildCard.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 13:40:30 by oal-tena          #+#    #+#             */
/*   Updated: 2022/12/20 06:53:50 by aaljaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/WildCard.hpp"
#include "../incl/Client.hpp"

/**
 * @brief Check if the  parameter is a wildcard
 */
bool ft::WildCard::is_wildCard(std::string const &str)
{
    if (str.find('*') != std::string::npos)
        return true;
    return false;
}

t_mask	*ft::WildCard::getMask(void)
{
	return (this->_masks);
}


/**
 * @brief Check if the parameter match the wildcard
 */
bool ft::WildCard::match_wildCard(std::string const &str, std::string const &wildcard)
{
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
    return false;
}

void ft::WildCard::split_mask(std::string &str)
{
    _masks = new t_mask;
    if (str.find_first_of('!') != std::string::npos && str.find_last_of('@') != std::string::npos)
    {
        _masks->nick = str.substr(0, str.find('!'));
        _masks->user = str.substr(str.find('!') + 1, str.find('@') - 2);
        _masks->host = str.substr(str.find('@') + 1);
    }
    else if (str.find('!') != std::string::npos && str.find_last_not_of('@') != std::string::npos)
    {
        _masks->nick = str.substr(0, str.find('!'));
        _masks->user = str.substr(str.find('!') + 1);
        return;
    }
    else if (str.find_first_of('@') != std::string::npos)
    {
        _masks->nick = str.substr(0, str.find('@'));
        _masks->host = str.substr(str.find('@') + 1);
        return;
    }
    else if (str.find_first_of('*') != std::string::npos)
    {
        _masks->wildcard = str;
        return;
    }
    else
    {
        _masks->nick = str;
        return;
    }
}

bool ft::WildCard::is_mask(void)
{
    // if (_masks->user )
    //     return false;
    return true;
}

bool ft::WildCard::match_client_mask(ft::Client *client)
{
    if (_masks->nick != "" && _masks->nick.size() > 1 && match_wildCard(client->getNickName(), _masks->nick) == false)
        return false;
    if (_masks->user != "" && _masks->user.size() > 1 && match_wildCard(client->getUserName(), _masks->user) == false)
        return false;
    if (_masks->host != "" && _masks->host.size() > 1 && match_wildCard(client->getHostName(), _masks->host) == false)
        return false;
    if (_masks->wildcard != "" && _masks->wildcard.size() > 1 && !match_wildCard(client->getNickName(), _masks->wildcard))
        return false;
    return true;
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
