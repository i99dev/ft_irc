/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Join.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isaad <isaad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 19:58:17 by oal-tena          #+#    #+#             */
/*   Updated: 2022/12/31 03:09:25 by isaad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef JOIN_HPP

#define JOIN_HPP

#include "./Command.hpp"

namespace ft
{
	class Join : public ft::Command
	{
	public:
		Join(void);
		void execute();
		int createCH(std::string, std::string);
		int breakers(std::string, int);
		void addClient(int);
		void split(std::vector<std::string> v, char seperator);
	};

}

#endif
