/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 20:00:14 by oal-tena          #+#    #+#             */
/*   Updated: 2022/12/31 16:24:41 by aaljaber         ###   ########.fr       */
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
		void	connectClientBack();
        void execute();
    };
}

#endif