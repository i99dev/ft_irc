/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cap.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oal-tena <oal-tena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 22:41:02 by oal-tena          #+#    #+#             */
/*   Updated: 2022/11/28 22:45:11 by oal-tena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef CAP_HPP
# define CAP_HPP

#include "./Command.hpp"

namespace ft
{
	class Cap : public ft::Command
	{
	public:
		Cap(void);
		void execute();
	};

}
#endif