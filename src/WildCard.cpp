/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WildCard.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oal-tena <oal-tena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 13:40:30 by oal-tena          #+#    #+#             */
/*   Updated: 2022/12/17 14:45:02 by oal-tena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/WildCard.hpp"
#include "../incl/Client.hpp"

/**
 * @brief Check if the  parameter is a wildcard
 */
bool ft::WildCard::is_wildCard(std::string const &str)
{
    if (str.find('*') != std::string::npos || str.find('?') != std::string::npos)
        return true;
    return false;
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

void ft::WildCard::split_mask(std::string &str)
{
    t_mask *mask;

    mask = new t_mask;
    if (str.find_first_of('!') != std::string::npos && str.find_last_of('@') != std::string::npos)
    {
        mask->nick = str.substr(0, str.find('!'));
        mask->user = str.substr(str.find('!') + 1, str.find('@') - 2);
        mask->host = str.substr(str.find('@') + 1);
        _masks.push_back(mask);
        return;
    }
    else if (str.find_first_of('!') != std::string::npos && str.find_last_not_of('@') != std::string::npos)
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

bool ft::WildCard::is_mask(void)
{
    if (_masks.empty())
        return false;
    return true;
}

bool ft::WildCard::match_client_mask(ft::Client *client)
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

ft::WildCard::WildCard(std::string const &str)
{
    std::string tmp = str;
    //check if the parameter is a mask
    if (is_wildCard(str))
    {
        split_mask(tmp);
    }
}


ft::WildCard::~WildCard(void)
{
    std::vector<t_mask *>::iterator it = _masks.begin();
    std::vector<t_mask *>::iterator ite = _masks.end();

    while (it != ite)
    {
        delete (*it);
        it++;
    }
}
