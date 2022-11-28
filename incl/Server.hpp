/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oal-tena <oal-tena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 10:54:14 by oal-tena          #+#    #+#             */
/*   Updated: 2022/11/28 19:48:21 by oal-tena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
#define SERVER_HPP

#include <iostream>
#include <string>
#include <arpa/inet.h>
#include <cstdlib>
#include <fcntl.h>
#include <unistd.h>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/poll.h>
#include <sys/select.h>
#include <cerrno>
#include <netdb.h>

// Our Headers...
#include "Client.hpp"
#include "Message.hpp"
#include "Channel.hpp"


namespace ft
{
    class Command;
    class Server
    {
    private:
        std::string const host;
        std::string const servername;
        std::string const version;
        std::string const port;
        std::string const password;
        int master_fd;     // file descriptor
        int master_socket; // new socket

    public:
        Server(std::string const &port, std::string const &password);
        ~Server();

        void acceptConnection();
        void receiveMessage(int i);

        std::vector<Client *> clients;
        std::vector<pollfd> fds;
        std::vector<Channel *> channels;
        std::map<std::string, ft::Command *> _commands;

        enum Status
        {
            OFFLINE,
            ONLINE,
            CLOSED
        } status;

        void create_socket();
        void createPoll();
        void setfd(int fd);
        void init_commands(void);
    };
}

#endif