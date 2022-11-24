/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oal-tena <oal-tena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 11:10:58 by oal-tena          #+#    #+#             */
/*   Updated: 2022/11/24 11:37:44 by oal-tena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/Server.hpp"
#include <netdb.h>

ft::Server::Server(std::string const &port, std::string const &password) : host("127.0.0.1"),
                                                                           servername("ft_irc"),
                                                                           version("0.1"),
                                                                           port(port),
                                                                           password(password)
{
    std::cout << "Server created" << std::endl;
    std::cout << "Host: " << host << std::endl;
    std::cout << "Port: " << port << std::endl;
    std::cout << "Password: " << password << std::endl;
    std::cout << "Servername: " << servername << std::endl;

    this->create_socket();
    this->createPoll();
}

ft::Server::~Server()
{
    std::cout << "Server destroyed" << std::endl;
}

/**
 * @brief Create a socket object
*/
void ft::Server::create_socket()
{
    int yes = 1;
    addrinfo hints, *servinfo;
    std::memset(&hints, 0, sizeof(addrinfo));

    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_CANONNAME;

    if (getaddrinfo(host.c_str(), this->port.c_str(), &hints, &servinfo) != 0)
    {
        std::cerr << "getaddrinfo" << std::endl;
        exit(1);
    }

    if ((this->master_fd = socket(servinfo->ai_family, servinfo->ai_socktype, servinfo->ai_protocol)) == -1)
    {
        std::cerr << "socket" << std::endl;
        exit(1);
    }

    if (setsockopt(this->master_fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1)
    {
        std::cerr << "setsockopt" << std::endl;
        exit(1);
    }

    if (bind(this->master_fd, servinfo->ai_addr, servinfo->ai_addrlen) == -1)
    {
        std::cerr << "bind" << std::endl;
        exit(1);
    }

    if (listen(this->master_fd, 10) == -1)
    {
        std::cerr << "listen" << std::endl;
        exit(1);
    }
    std::cout << "Server listening on " << std::endl;
}

/**
 * @brief Create a Poll object
*/
void ft::Server::createPoll()
{
    pollfd pfd;
    pfd.fd = this->master_fd;
    pfd.events = POLLIN;
    this->fds.push_back(pfd);

    std::cout << "Server is online" << std::endl;

    while (1)
    {
        int ret = poll(&this->fds[0], this->fds.size(), -1);
        if (ret == -1)
        {
            std::cerr << "poll" << std::endl;
            exit(1);
        }
        else if (ret > 0)
        {
            for (size_t i = 0; i < this->fds.size(); i++)
            {
                if (this->fds[i].revents & POLLIN)
                {
                    if (this->fds[i].fd == this->master_fd)
                    {
                        this->acceptConnection();
                    }
                    else
                    {
                        this->receiveMessage(i);
                    }
                }
            }
        }
    }
}

/**
 * @brief tools to get the client's ip address
*/
void *get_in_addr(struct sockaddr *sa)
{
    if (sa->sa_family == AF_INET)
        return &(((struct sockaddr_in *)sa)->sin_addr);
    return &(((struct sockaddr_in6 *)sa)->sin6_addr);
}

/**
 * @brief Accept a new connection
*/
void ft::Server::acceptConnection()
{
    int new_fd;
    sockaddr_storage their_addr;
    their_addr.ss_family = AF_INET;
    their_addr.__ss_align = 0;
    socklen_t addr_size = sizeof(their_addr);
    char ip_client[INET6_ADDRSTRLEN];

    if ((new_fd = accept(master_fd, (sockaddr *)&their_addr, &addr_size)) == -1)
    {
        std::cerr << "accept" << std::endl;
        exit(1);
    }

    inet_ntop(their_addr.ss_family, get_in_addr((sockaddr *)&their_addr), ip_client, sizeof(ip_client));
    Client *client = new Client(new_fd, servername, ip_client);
    this->clients.push_back(client);
    pollfd pfd;
    pfd.fd = new_fd;
    pfd.events = POLLIN;
    pfd.revents = 0;
    fds.push_back(pfd);
}

/**
 * @brief Receive message from client
*/
void ft::Server::receiveMessage(int i)
{
    int nbytes;
    char buf[1024];
    nbytes = recv(fds[i].fd, buf, 1024, 0);
    if (nbytes <= 0)
    {
        if (nbytes == 0)
        {
            std::cout << "socket " << fds[i].fd << " hung up" << std::endl;
        }
        else
        {
            std::cerr << "recv" << std::endl;
        }
        close(fds[i].fd);
        fds.erase(fds.begin() + i);
    }
    else
    {
        buf[nbytes] = '\0';
        Message message = Message(buf, fds[i].fd);
        this->clients[i - 1]->setMsgSend(message);         
    }
}

