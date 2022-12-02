/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mode_List.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 00:55:38 by aaljaber          #+#    #+#             */
/*   Updated: 2022/12/03 00:01:40 by aaljaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/Mode_List.hpp"

inline ft::Channel_Mode	ft::ModeTools::findChannelMode(char mode)
{
	for (int i = 1; i < CHMODE_NUM; ++i)
	{
		if (CHMODE_CHAR[i] == mode)
			return (CHMODE_ENUM[i]);
	}
	return (ft::NO_MODE);
}

inline ft::User_Mode	ft::ModeTools::findUserMode(char mode)
{
	for (int i = 0; i < USMODE_NUM; ++i)
	{
		if (USMODE_CHAR[i] == mode)
			return (USMODE_ENUM[i]);
	}
	return (ft::n_NO_MODE);
}

inline bool	ft::ModeTools::isCHMode(char mode)
{
	for (int i = 1; i < CHMODE_NUM; ++i)
	{
		if (CHMODE_CHAR[i] == mode)
			return (true);
	}
	return (false);
}

inline bool	ft::ModeTools::isUSMode(char mode)
{
	for (int i = 0; i < USMODE_NUM; ++i)
	{
		if (USMODE_CHAR[i] == mode)
			return (true);
	}
	return (false);	
}
