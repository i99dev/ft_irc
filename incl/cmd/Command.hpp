/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 04:10:43 by aaljaber          #+#    #+#             */
/*   Updated: 2022/11/23 04:20:22 by aaljaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"


class Command
{
	protected:
		std::string _command;
		std::string *_parameters;	
	public:
		Command(std::string command, std::string *parameters);
		~Command();
};

Command::Command(std::string command, std::string *parameters):_command(command)
{
	int	i;

	i = -1;
	_parameters = new std::string [parameters->length()];
	while (++i < parameters->length())
		_parameters[i] = parameters[i];
}

Command::~Command()
{
	delete[] _parameters;
}
