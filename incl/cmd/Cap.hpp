/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cap.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oal-tena <oal-tena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 06:45:26 by oal-tena          #+#    #+#             */
/*   Updated: 2022/11/30 06:54:11 by oal-tena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAP_HPP

#define CAP_HPP

#include "./Command.hpp"

namespace ft
{
    class Command;
    class Cap : public Command
    {
    public:
        Cap(void);
        void execute();
    };
}

#endif