/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Topic.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 07:32:13 by aaljaber          #+#    #+#             */
/*   Updated: 2022/12/08 07:33:14 by aaljaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOPIC_HPP

#define TOPIC_HPP

#include "./Command.hpp"

namespace ft
{
	class Topic : public ft::Command
	{
	public:
		Topic(void);
		void execute();
	};

}

#endif