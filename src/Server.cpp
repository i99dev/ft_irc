/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isaad <isaad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 11:10:58 by oal-tena          #+#    #+#             */
/*   Updated: 2022/12/10 23:50:18 by isaad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/Server.hpp"

//command functions
#include "../incl/cmd/User.hpp"
#include "../incl/cmd/Join.hpp"
#include "../incl/cmd/Nick.hpp"
#include "../incl/cmd/Invite.hpp"
#include "../incl/cmd/Whois.hpp"
#include "../incl/cmd/Who.hpp"
#include "../incl/cmd/Cap.hpp"
#include "../incl/cmd/Mode.hpp"
#include "../incl/cmd/Ping.hpp"
#include "../incl/cmd/PrivMsg.hpp"
#include "../incl/cmd/Part.hpp"
#include "../incl/cmd/Kick.hpp"
#include "../incl/cmd/Notice.hpp"
#include "../incl/cmd/Topic.hpp"
#include "../incl/cmd/List.hpp"



ft::Server::Server(std::string const &port, std::string const &password) : host("127.0.0.1"),
                                                                           servername("42_irc"),
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
    init_commands();
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
    hints.ai_flags = AI_PASSIVE;

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
		// VALGRIND_DO_LEAK_CHECK ;
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
        std::vector <Message *> args = ft::Server::splitMessage(buf, '\n', fds[i].fd);
        for (size_t k = 0; k < args.size(); k++)
        {
            this->clients[i - 1]->setMsgSend(args[k]);
            std::map<std::string, Command *>::iterator it;
            if ((it = _commands.find(args[k]->getCommand())) != _commands.end())
            {
                Command *cmd = it->second;
                cmd->setClient(this->clients[i - 1]);
                cmd->setServer(this);
                cmd->setMessage(args[k]);
                cmd->execute();
            }
            else
            {
                this->clients[i - 1]->sendReply("ERROR :Unknown command\r \n");
            }
        }
    }
}

void ft::Server::init_commands(void)
{
    _commands["JOIN"] = new ft::Join();
    _commands["USER"] = new ft::User();
    _commands["NICK"] = new ft::Nick();
    _commands["KICK"] = new ft::Kick();
    _commands["WHOIS"] = new ft::Whois();
    _commands["WHO"] = new ft::Who();
    _commands["CAP"] = new ft::Cap();
    _commands["MODE"] = new ft::Mode();
    _commands["PING"] = new ft::Ping();
    _commands["PART"] = new ft::Part();
    _commands["PRIVMSG"] = new ft::Privmsg();
    _commands["NOTICE"] = new ft::Notice();
    _commands["INVITE"] = new ft::Invite();
    _commands["TOPIC"] = new ft::Topic();
    _commands["LIST"] = new ft::List();

}

/**
 * @brief split Message by newlines to to be multiple messages
*/

std::vector<ft::Message *> ft::Server::splitMessage(std::string msg, char delim, int fd)
{
    std::vector<ft::Message *> messages;
    std::stringstream ss(msg);
    std::string item;
    while (std::getline(ss, item, delim))
    {
        ft::Message *message = new ft::Message(item.substr(0, item.size() - 1), fd);
        messages.push_back(message);
    }
    return messages;
}

/**
 * @brief get Channels list
*/

std::vector<ft::Channel *> ft::Server::getChannels()
{
    return this->channels;
}

/**
 * @brief get Clients list
*/
std::vector<ft::Client *> ft::Server::getClients()
{
    return this->clients;
}

/**
 * @brief get Server name
*/
std::string ft::Server::getServerName()
{
    return this->servername;
}

/**
 * @brief get Server port
*/

std::string ft::Server::getPort()
{
    return this->port;
}

void ft::Server::sendReply(Client *client, std::string reply)
{
    std::string msg = reply;
    send(client->fd, msg.c_str(), msg.size(), 0);
}

bool ft::Server::isNickNameTaken(std::string nickname)
{
    for (size_t i = 0; i < this->clients.size(); i++)
    {
        if (this->clients[i]->getNickName() == nickname)
            return true;
    }
    return false;
}

std::string ft::Server::getVersion()
{
    return this->version;
}

void ft::Server::checkConnection()
{
    for (size_t i = 0; i < this->clients.size(); i++)
    {
        if (this->clients[i]->getPing() == 0)
        {
            this->clients[i]->sendReply("ERROR :Closing Link: " + this->clients[i]->getIp() + " (Ping timeout: 120 seconds)\r \n");
            this->clients.erase(this->clients.begin() + i);
        }
        else
        {
            this->clients[i]->setPing(this->clients[i]->getPing() - 1);
        }
    }
}

bool		ft::Server::isChannel(std::string CHname)
{
	for (long unsigned int i = 0; i < this->channels.size(); i++)
	{
		if (this->channels[i]->getChName() == CHname)
			return (true);
	}
	return (false);
}

ft::Channel	*ft::Server::getChannel(std::string CHname)
{
	for (long unsigned int i = 0; i < this->channels.size(); i++)
	{
		if (this->channels[i]->getChName() == CHname)
			return (this->channels[i]);
	}
	return (NULL);
}
