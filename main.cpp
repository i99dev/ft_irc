/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oal-tena <oal-tena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 10:55:16 by oal-tena          #+#    #+#             */
/*   Updated: 2022/11/08 11:30:43 by oal-tena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "incl/Server.hpp"

int main(int argc, char **argv)
{
    if (argc != 4)
    {
        std::cout << "Usage: ./ft_irc <host> <port>" << std::endl;
        return (1);
    }
    ft::Server server(argv[1], argv[2], argv[3]);
    return 0;
}