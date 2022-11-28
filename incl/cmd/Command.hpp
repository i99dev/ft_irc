/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oal-tena <oal-tena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 04:10:43 by aaljaber          #+#    #+#             */
/*   Updated: 2022/11/28 20:54:24 by oal-tena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "../Server.hpp"

namespace ft
{
	class Command
	{
	protected:
		// std::vector<ft::Channel *> &channels;
		// std::vector<ft::Client *> &clients;
		// ft::Client *client;
		// std::vector<pollfd> _fds;
		// std::string command;

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
			std::cout << "Command " << _name << " destructor called" << std::endl;
		};
		virtual void execute() = 0;

		//methods
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
