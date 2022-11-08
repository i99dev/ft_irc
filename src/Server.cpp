/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oal-tena <oal-tena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 11:10:58 by oal-tena          #+#    #+#             */
/*   Updated: 2022/11/08 12:25:37 by oal-tena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/Server.hpp"

ft::Server::Server(std::string const &host, std::string const &port, std::string const &password):
    host(host),
    servername("ft_irc"),
    version("0.1"),
    port(port),
    password(password)
{
    std::cout << "Server created" << std::endl;
    std::cout << "Host: " << host << std::endl;
    std::cout << "Port: " << port << std::endl; 
    std::cout << "Password: " << password << std::endl;

    create_socket();
    accept_connection();
    send_message();
    receive_message();
    close_connection();
    close_socket();
    close_server();
    
}

void ft::Server::create_socket()
{
    int fd;
    struct sockaddr_in addr;
    int opt = 1;

    if ((fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        std::cout << "Socket failed" << std::endl;
        exit(EXIT_FAILURE);
    }
    if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
    {
        std::cout << "Setsockopt failed" << std::endl;
        exit(EXIT_FAILURE);
    }
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(atoi(port.c_str()));
    if (bind(fd, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        std::cout << "Bind failed" << std::endl;
        exit(EXIT_FAILURE);
    }
    if (listen(fd, 3) < 0)
    {
        std::cout << "Listen failed" << std::endl;
        exit(EXIT_FAILURE);
    }
    std::cout << "Server running" << std::endl;
}

void ft::Server::accept_connection()
{
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    if ((new_socket = accept(fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0)
    {
        std::cout << "Accept failed" << std::endl;
        exit(EXIT_FAILURE);
    }
    std::cout << "New connection" << std::endl;
}

void ft::Server::send_message()
{
    char buffer[1024] = {0};
    std::string message;
    std::cout << "Enter message: ";
    std::getline(std::cin, message);
    strcpy(buffer, message.c_str());
    send(new_socket, buffer, strlen(buffer), 0);
    std::cout << "Message sent" << std::endl;
}

void ft::Server::receive_message()
{
    char buffer[1024] = {0};
    int valread;
    if ((valread = read(new_socket, buffer, 1024)) == 0)
    {
        std::cout << "Client disconnected" << std::endl;
        exit(EXIT_FAILURE);
    }
    std::cout << "Message received: " << buffer << std::endl;
}

void ft::Server::close_connection()
{
    close(new_socket);
    std::cout << "Connection closed" << std::endl;
}

void ft::Server::close_socket()
{
    close(fd);
    std::cout << "Socket closed" << std::endl;
}

void ft::Server::close_server()
{
    close_connection();
    close_socket();
    std::cout << "Server closed" << std::endl;
}

void ft::Server::run()
{
    create_socket();
    accept_connection();
    while (1)
    {
        send_message();
        receive_message();
    }
    close_server();
}



ft::Server::~Server()
{
    std::cout << "Server destroyed" << std::endl;
}