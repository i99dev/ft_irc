/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 04:10:43 by aaljaber          #+#    #+#             */
/*   Updated: 2022/12/29 16:53:49 by aaljaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "../Server.hpp"
#include "../Replies.hpp"
# define BBLK "\e[1;30m"
# define BRED "\e[1;31m"
# define BGRN "\e[1;32m"
# define BYEL "\e[1;33m"
# define BBLU "\e[1;34m"
# define BMAG "\e[1;35m"
# define BCYN "\e[1;36m"
# define BWHT "\e[1;37m"
# define BPUR "\e[0;35m"
# define DEFCOLO "\033[0m"

namespace ft
{
	class Command
	{
	protected:
		std::string _name;
		std::string _description;
		std::string _usage;

		Client *_client;
		Server *_server;
		Message *_message;

	public:
		Command(void){};
		virtual ~Command()
		{
			std::cout << BGRN << "Command " << _name << " destructor called" << DEFCOLO << std::endl;
		};
		virtual void execute() = 0;
		virtual bool validate(void)
		{
			return (true);
		}
		void setClient(Client *client)
		{
			_client = client;
		}

		void setServer(Server *server)
		{
			_server = server;
		}

		void setMessage(Message *message)
		{
			_message = message;
		}
		
		//getters
		std::string getName()
		{
			return _name;
		}

		std::string getDescription()
		{
			return _description;
		}

		std::string getUsage()
		{
			return _usage;
		}
	};
}
