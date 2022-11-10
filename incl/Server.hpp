/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oal-tena <oal-tena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 10:54:14 by oal-tena          #+#    #+#             */
/*   Updated: 2022/11/10 08:58:24 by oal-tena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

# include <iostream>
# include <string>
# include <arpa/inet.h>
# include <cstdlib>
# include <fcntl.h>
# include <unistd.h>
# include <cstring>
# include <sys/types.h>
# include <sys/socket.h>
# include <sys/poll.h>
#include <sys/select.h>

# include "Client.hpp"
# include "Message.hpp"

# define EINTR 4

# define EXIT_FAILURE 1
# define errno 1
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
            std::vector<Client *> clients;
            int fd; // file descriptor
            int master_socket; // new socket
            enum Status {
                OFFLINE,
                ONLINE,
                CLOSED
            } status;
            std::vector<struct pollfd> fds;
            Server(std::string const &port, std::string const &password);
            void run();
            void create_socket();
            void accept_connection();
            void send_message();
            void receive_message();
            void close_connection();
            void close_socket();
            void close_server();
            ~Server();
    };
}

#endif