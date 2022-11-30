/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oal-tena <oal-tena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 10:54:14 by oal-tena          #+#    #+#             */
/*   Updated: 2022/11/30 08:24:04 by oal-tena         ###   ########.fr       */
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
#include <sstream>

#define HOST "127.0.0.1"
#define CRLF "\r\n"


// Our Headers...
#include "Client.hpp"
#include "Message.hpp"
#include "Channel.hpp"

namespace ft
{
    class Channel;
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

        std::vector<ft::Client *> clients;
        std::vector<pollfd> fds;
        std::vector<Channel *> channels;
        std::map<std::string, ft::Command *> _commands;

        enum Status
        {
            OFFLINE,
            ONLINE,
            CLOSED
        } status;

        enum MessageKind
        {
            ERROR,
            NOTE,
            WARNING,
            INFO,
            DEBUG
        };

        void create_socket();
        void createPoll();
        void setfd(int fd);
        void init_commands(void);
        std::vector<ft::Message *> splitMessage(std::string msg, char delim, int fd);

        // channel functions
        std::vector<Channel *> getChannels();

        // server functions
        std::string getHost();
        std::string getServerName();
        std::string getVersion();
        std::string getPort();

        // client functions
        std::vector<Client *> getClients();
        bool isNickNameTaken(std::string nickName);

        // message functions
        void sendReply(Client *client, std::string msg);
    };
}

#endif