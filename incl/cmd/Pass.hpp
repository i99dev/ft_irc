/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pass.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 10:10:52 by aaljaber          #+#    #+#             */
/*   Updated: 2022/12/30 10:12:43 by aaljaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PASS_HPP
#define PASS_HPP
#include "./Command.hpp"

namespace ft
{
    class Command;
    class Pass : public Command
    {
    public:
        Pass(void);
        void						execute(void);
	};
}

#endif