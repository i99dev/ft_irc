/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Invite.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isaad <isaad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 06:45:26 by oal-tena          #+#    #+#             */
/*   Updated: 2022/12/09 20:20:52 by isaad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INVITE_HPP

#define INVITE_HPP

#include "./Command.hpp"

namespace ft
{
    class Command;
    class Invite : public Command
    {
    public:
        Invite(void);
        void execute();
    };
}

#endif