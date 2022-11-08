/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oal-tena <oal-tena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 10:54:14 by oal-tena          #+#    #+#             */
/*   Updated: 2022/11/08 11:20:24 by oal-tena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

# include <iostream>
# include <string>


namespace ft
{
    class Server
    {
        private:
            std::string const host;
            std::string const servername;
            std::string const version;
            std::string const port;
            std::string const password;
        public:
            Server(std::string const &host, std::string const &port, std::string const &password);
            ~Server();
    };
}

#endif