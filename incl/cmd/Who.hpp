/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Who.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isaad <isaad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 06:46:59 by oal-tena          #+#    #+#             */
/*   Updated: 2022/12/06 13:02:55 by isaad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WHO_HPP

#define WHO_HPP

#include "./Command.hpp"

namespace ft
{
    class Command;
    class Who : public Command
    {
    public:
        Who(void);
        void execute();
    };
}

#endif