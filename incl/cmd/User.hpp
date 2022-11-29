/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oal-tena <oal-tena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 20:00:14 by oal-tena          #+#    #+#             */
/*   Updated: 2022/11/28 21:06:46 by oal-tena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef USER_HPP

#define USER_HPP

#include "./Command.hpp"

namespace ft
{
    class Command;
    class User : public Command
    {
    public:
        User(void);
        void execute();
    };
}

#endif