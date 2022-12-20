/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mask.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 13:36:40 by oal-tena          #+#    #+#             */
/*   Updated: 2022/12/20 09:01:25 by aaljaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef Mask_HPP
#define Mask_HPP
#include <string>
#include <vector>

struct _mask
{
    std::string nick;
    std::string user;
    std::string host;
} typedef t_mask;

namespace ft
{
    class Client;
    
    class Mask
    {
    private:
        t_mask *_masks;
		bool	is_WildCard;
		bool	is_mask;

    public:
        Mask(std::string const &str);
        ~Mask();
        bool match_wildCard(std::string const &str, std::string const &wildcard);
        void split_mask(std::string  &str);
        bool match_client_mask(ft::Client *client);
		t_mask	*getMask();
    };
}

#endif