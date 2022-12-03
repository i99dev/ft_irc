/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mode_List.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 00:55:38 by aaljaber          #+#    #+#             */
/*   Updated: 2022/12/03 04:12:46 by aaljaber         ###   ########.fr       */
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

inline char	ft::ModeTools::getCHModechar(ft::Channel_Mode mode)
{
	for (int i = 1; i < CHMODE_NUM; ++i)
	{
		if (CHMODE_ENUM[i] == mode)
			return (CHMODE_CHAR[i]);
	}
	return ('N');
}

inline char	ft::ModeTools::getUSModechar(ft::User_Mode mode)
{
	for (int i = 0; i < USMODE_NUM; ++i)
	{
		if (USMODE_ENUM[i] == mode)
			return (USMODE_CHAR[i]);
	}
	return ('n');
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
