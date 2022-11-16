/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oal-tena <oal-tena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 10:55:16 by oal-tena          #+#    #+#             */
/*   Updated: 2022/11/15 07:13:20 by oal-tena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "incl/Server.hpp"

int main(int argc, char **argv)
{
    if (argc != 3)
    {
        std::cout << "Usage: ./ircserv [port] [password]" << std::endl;
        return (EXIT_FAILURE);
    }
    ft::Server server(argv[1], argv[2]);
    return 0;
}


