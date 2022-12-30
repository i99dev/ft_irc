/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isaad <isaad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 20:00:14 by oal-tena          #+#    #+#             */
/*   Updated: 2022/12/30 22:11:57 by isaad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef USER_HPP

#define USER_HPP

#include "./Command.hpp"
#include "../Replies.hpp"

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