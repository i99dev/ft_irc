/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oal-tena <oal-tena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 10:55:16 by oal-tena          #+#    #+#             */
/*   Updated: 2022/12/21 08:08:59 by oal-tena         ###   ########.fr       */
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
    //check password
    if (strlen(argv[2]) < 6)
    {
        std::cout << "Password must be at least 6 characters" << std::endl;
        return (EXIT_FAILURE);
    }
    //check port
    int port = atoi(argv[1]);
    if (port < 1024 || port > 65535)
    {
        std::cout << "Port must be between 1024 and 65535" << std::endl;
        return (EXIT_FAILURE);
    }
    ft::Server server(argv[1], argv[2]);
    //destroy server
    delete &server;
    return 0;
}


