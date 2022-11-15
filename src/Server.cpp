/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oal-tena <oal-tena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 11:10:58 by oal-tena          #+#    #+#             */
/*   Updated: 2022/11/15 07:42:14 by oal-tena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/Server.hpp"

ft::Server::Server(std::string const &port, std::string const &password):
    host("localhost"),
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

void ft::Server::create_socket()
{
    struct sockaddr_in addr; // option to add to master_fd 
    int opt = 1;
    /**
     * Creating socket file descriptor
     * AF_INET: IPv4
     * SOCK_STREAM: TCP
     * 0: Default protocol
     */ 
    if ((master_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        std::cout << "Socket failed" << std::endl;
        exit(EXIT_FAILURE);
    }
    /**
     * Forcefully attaching socket to the port 8080
     * SO_REUSEADDR: Reuse the address
     * SO_REUSEPORT: Reuse the port
     * SOL_SOCKET: Socket layer itself
     * &opt: Pointer to the option value
     * sizeof(opt): Size of the option value
     */
    if (setsockopt(master_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)))
    {
        std::cout << "Setsockopt failed" << std::endl;
        exit(EXIT_FAILURE);
    }
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(atoi(port.c_str()));
    /**
     * Forcefully attaching socket to the port 8080
     * fd: Socket file descriptor
     * (struct sockaddr *)&addr: Pointer to the address
     * sizeof(addr): Size of the address
     */
    if (bind(master_fd, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        std::cout << "Bind failed" << std::endl;
        exit(EXIT_FAILURE);
    }
    if (listen(master_fd, 3) < 0)
    {
        std::cout << "Listen failed" << std::endl;
        exit(EXIT_FAILURE);
    }
    std::cout << "Server running" << std::endl;
}

void ft::Server::createPoll()
{
    pollfd pfd;
    pfd.fd = master_fd;
    pfd.events = POLLIN;
    fds.push_back(pfd);

    while (1)
    {
        int ret = poll(fds.data(), fds.size(), -1);
        if (ret == -1)
        {
            if (errno == EINTR)
                continue;
            std::cout << "Poll failed" << std::endl;
            exit(EXIT_FAILURE);
        }
        for (size_t i = 0; i < fds.size(); i++)
        {
            if (fds[i].revents & POLLIN)
            {
                if (fds[i].fd == master_fd)
                {
                    struct sockaddr_in addr;
                    socklen_t addrlen = sizeof(addr);
                    int client_fd = accept(master_fd, (struct sockaddr *)&addr, &addrlen);
                    if (client_fd == -1)
                    {
                        std::cout << "Accept failed" << std::endl;
                        exit(EXIT_FAILURE);
                    }
                    std::cout << "New connection" << std::endl;
                    Client client(client_fd);
                    clients.push_back(&client);
                    struct pollfd pfd;
                    pfd.fd = client_fd;
                    pfd.events = POLLIN;
                    fds.push_back(pfd);
                }
                else if (i > 0)
                {
                    //print client number and message
                    std::cout << "Client " << clients[i - 1]->fd << " sent a message" << std::endl;
                    char buffer[1024] = {0}; // 1024 is the max size of the message
                    int valread = read(fds[i].fd, buffer, 1024); // read from client
                    if (valread == 0)
                    {
                        std::cout << "Client disconnected" << std::endl;
                        close(fds[i].fd);
                        fds.erase(fds.begin() + i);
                        clients.erase(clients.begin() + i - 1);
                        continue;
                    }
                    std::cout << "Message received: " << buffer << std::endl;
                    std::string msg(buffer);
                }
            }
        }
    }
}


ft::Server::~Server()
{
    std::cout << "Server destroyed" << std::endl;
}