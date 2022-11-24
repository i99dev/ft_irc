/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isaad <isaad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 04:10:43 by aaljaber          #+#    #+#             */
/*   Updated: 2022/11/24 09:04:04 by isaad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <vector>
#include "../Channel.hpp"
#include "../Server.hpp"
#include "../Client.hpp"

namespace ft{
	class Command
	{
		protected:
			std::vector<ft::Channel *> &channels;
			std::vector<ft::Client *> &clients;
			ft::Client *client;
			std::vector<pollfd> _fds;
			std::string command;
		public:
			Command(std::vector<ft::Channel *> &_channels, ft::Client *_client, std::vector<pollfd> _fds, std::vector<ft::Client *> &clients);
			~Command();
	};
}