/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WildCard.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oal-tena <oal-tena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 13:36:40 by oal-tena          #+#    #+#             */
/*   Updated: 2022/12/19 17:25:18 by oal-tena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WILDCARD_HPP
#define WILDCARD_HPP
#include <string>
#include <vector>

struct _mask
{
    std::string nick;
    std::string user;
    std::string host;
    std::string wildcard; // use ex : general* or *general
} typedef t_mask;

namespace ft
{
    class Client;
    
    class WildCard
    {
    private:
        t_mask *_masks;

    public:
        WildCard(std::string const &str);
        ~WildCard();
        bool is_wildCard(std::string const &str);
        bool match_wildCard(std::string const &str, std::string const &wildcard);
        void split_mask(std::string  &str);
        bool is_mask();
        bool match_client_mask(ft::Client *client);
    };
}

#endif