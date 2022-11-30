/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mode_List.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 18:35:36 by aaljaber          #+#    #+#             */
/*   Updated: 2022/12/01 02:38:17 by aaljaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MODE_LIST_HPP
#define MODE_LIST_HPP
#define	CHMODE_NUM 11
#define CHMODE_CHAR (char []){'C', 'N', 'O', 'o', 'v', 'i', 'm', 'p', 't', 'k', 'l'}
#define CHMODE_ENUM (Channel_Mode []){CLEAR_MODE, NO_MODE, O_CHANNEL_CREATOR, o_OPERATOR_PRIVILEGE, v_VOICE_PRIVILEGE,i_INVITE_ONLY_CHANNEL, m_MODERATED_CHANNEL, p_PRIVATE_CHANNEL, t_TOPIC, k_CAHNNEL_PASSWORD, l_USER_LIMIT}
#define	USMODE_NUM 3
#define USMODE_CHAR (char []){'n', 'o', 'i'}
#define USMODE_ENUM (User_Mode []){n_NO_MODE, o_OPERATOR_FLAG, i_INVISIBLE}

// TODO: change the loop of checking the modes to start with the valid modes

namespace ft
{
	enum Channel_Mode
	{
		CLEAR_MODE, // ? used to state that the member doesn't have a mode; 
		NO_MODE, // ? not an available mode (used for check purposes);
		O_CHANNEL_CREATOR, // ? "channel creator" status (first join);
		o_OPERATOR_PRIVILEGE, // ? give/take(+/-) operator privelege to a member;
		v_VOICE_PRIVILEGE, // ? give/take(+/-) speak privelege to a member;
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
}

#endif
