/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mode_List.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 18:35:36 by aaljaber          #+#    #+#             */
/*   Updated: 2022/12/21 05:30:35 by aaljaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MODE_LIST_HPP
#define MODE_LIST_HPP
#define	CHMODE_NUM 14
#define CHMODE_CHAR (char []){'C', 'N', 'O', 'o', 'v', 'b', 'I', 'e', 'i', 'm', 'p', 't', 'k', 'l'}
#define CHMODE_ENUM (ft::Channel_Mode []){ft::CLEAR_MODE, ft::NO_MODE, ft::O_CHANNEL_CREATOR, ft::o_OPERATOR_PRIVILEGE, ft::v_VOICE_PRIVILEGE, ft::b_BAN_MASK, ft::I_INVITATION_MASK, ft::e_EXCEPTION_MASK, ft::i_INVITE_ONLY_CHANNEL, ft::m_MODERATED_CHANNEL, ft::p_PRIVATE_CHANNEL, ft::t_TOPIC, ft::k_CAHNNEL_PASSWORD, ft::l_USER_LIMIT}
#define	USMODE_NUM 3
#define USMODE_CHAR (char []){'n', 'o', 'i'}
#define USMODE_ENUM (ft::User_Mode []){ft::n_NO_MODE, ft::o_OPERATOR_FLAG, ft::i_INVISIBLE}
#define REMOVE '-'
#define SET '+'
#define QUERY 1
#define CHANGE 2
#define	MODEPARAMPOS 2

namespace ft
{
	enum Channel_Mode
	{
		CLEAR_MODE, // ? used to state that the member doesn't have a mode; 
		NO_MODE, // ? not an available mode (used for check purposes);
		O_CHANNEL_CREATOR, // ? "channel creator" status (first join);
		o_OPERATOR_PRIVILEGE, // ? give/take(+/-) operator privelege to a member;
		v_VOICE_PRIVILEGE, // ? give/take(+/-) speak privelege to a member;
		b_BAN_MASK, // ? to keep users out
		I_INVITATION_MASK, // ? to automatically override the invite-only flag
		e_EXCEPTION_MASK, // ? to override a ban mask
		i_INVITE_ONLY_CHANNEL, //? invite-only channel flag;
		m_MODERATED_CHANNEL, //? moderated channel (only operators and voice memebers speak) flag;
		p_PRIVATE_CHANNEL, //? private channel (invited & correct password) flag;
		t_TOPIC, // ? topic (only set by operators);
		k_CAHNNEL_PASSWORD, //? set/remove(+/-) the channel key (password);
		l_USER_LIMIT, //? set/remove(+/-) the user limit to channel;
	};
	enum User_Mode
	{
		n_NO_MODE,
		o_OPERATOR_FLAG, // ? operator Client (can be set using OPER);
		i_INVISIBLE, //? invisible status (set by USER and MODE);
	};
	namespace	ModeTools
	{
		Channel_Mode				findChannelMode(char mode);
		User_Mode					findUserMode(char mode);
		bool						isCHMode(char mode);
		bool						isMEMode(char mode);
		bool						isUSMode(char mode);
		bool						isCHflag(char mode);
		char						getCHModechar(ft::Channel_Mode mode);
		char						getUSModechar(ft::User_Mode mode);
		bool						isParamMode(char mode);
	}
}

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
	for (int i = 8; i < CHMODE_NUM; ++i)
	{
		if (CHMODE_CHAR[i] == mode)
			return (true);
	}
	return (false);
}

inline bool	ft::ModeTools::isCHflag(char mode)
{
	for (int i = 5; i < 9; ++i)
	{
		if (CHMODE_CHAR[i] == mode)
			return (true);
	}
	return (false);
}

inline bool	ft::ModeTools::isMEMode(char mode)
{
	for (int i = 2; i < 5; ++i)
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

inline char	ft::ModeTools::getCHModechar(ft::Channel_Mode mode)
{
	for (int i = 2; i < CHMODE_NUM; ++i)
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

inline bool	ft::ModeTools::isParamMode(char mode)
{
	if (mode == 'l' || mode == 'k' || mode == 'o' || mode == 'v' || mode == 'b' || mode == 'I' || mode == 'e')
		return (true);
	return (false);
}

#endif
