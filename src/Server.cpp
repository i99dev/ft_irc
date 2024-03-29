/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 11:10:58 by oal-tena          #+#    #+#             */
/*   Updated: 2023/01/05 07:20:24 by aaljaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/Server.hpp"

// command functions
#include "../incl/cmd/User.hpp"
#include "../incl/cmd/Join.hpp"
#include "../incl/cmd/Nick.hpp"
#include "../incl/cmd/Invite.hpp"
#include "../incl/cmd/Whois.hpp"
#include "../incl/cmd/Cap.hpp"
#include "../incl/cmd/Mode.hpp"
#include "../incl/cmd/Ping.hpp"
#include "../incl/cmd/PrivMsg.hpp"
#include "../incl/cmd/Part.hpp"
#include "../incl/cmd/Kick.hpp"
#include "../incl/cmd/Notice.hpp"
#include "../incl/cmd/Topic.hpp"
#include "../incl/cmd/List.hpp"
#include "../incl/cmd/Pong.hpp"
#include "../incl/cmd/Quit.hpp"
#include "../incl/cmd/Pass.hpp"
#include <string.h>
#include <cstring>


std::string storage = "";

#include <signal.h>
bool closeServer = false;
// close app by ctrl+c or ctrl+d
void sig_handler(int signo)
{
    if (signo == SIGINT)
    {
        std::cout << std::endl;
        closeServer = true;
    }
}

ft::Server::Server(std::string const &port, std::string const &password) : host("127.0.0.1"),
                                                                           servername("42_irc"),
                                                                           version("0.1"),
                                                                           port(port),
                                                                           password(password),
																		   CLIENTISBACK(false)
{
	
	std::cout << std::endl << BYEL;
	std::cout << "   ___ ___    _    ___ ____   ____ ____  _____ ______     __" << std::endl;
	std::cout << "  / _ \\_ _|  / \\  |_ _|  _ \\ / ___/ ___|| ____|  _ \\ \\   / /" << std::endl;
	std::cout << " | | | | |  / _ \\  | || |_) | |   \\___ \\|  _| | |_) \\ \\ / / " << std::endl;
	std::cout << " | |_| | | / ___ \\ | ||  _ <| |___ ___) | |___|  _ < \\ V /  " << std::endl;
	std::cout << "  \\___/___/_/   \\_\\___|_| \\_\\____|____/ |_____|_| \\_\\ \\_/   " << std::endl;	
	std::cout << BCYN << std::endl;
	std::cout << "			.--. 				" << std::endl;
	std::cout << "			|__| .-------.		" << std::endl;
	std::cout << "			|=.| |.-----.| 		" << std::endl;
	std::cout << "			|--| || "<< BYEL << "KCK" << BCYN << " ||		" << std::endl;
	std::cout << "			|  | |'-----'|		" << std::endl; 
	std::cout << "			|__|~')_____(' 		" << std::endl;
    std::cout << DEFCOLO << std::endl;                                                        

    std::cout << BCYN << "Server created" << std::endl;
    std::cout << BCYN << "Host: " << DEFCOLO <<  host << std::endl;
    std::cout << BCYN << "Port: " << DEFCOLO << port << std::endl;
    std::cout << BCYN << "Password: " << DEFCOLO << password << std::endl;
    std::cout << BCYN << "Servername: " << DEFCOLO << servername << std::endl;

    this->create_socket();
    init_commands();
    this->createPoll();
}

ft::Server::~Server()
{
    // close all sockets
    for (size_t i = 0; i < clients.size(); i++)
    {
        close(clients[i]->fd);
        delete clients[i];
    }
    close(master_fd);

    // delete all channels
    for (std::vector<Channel *>::iterator it = channels.begin(); it != channels.end(); it++)
    {
        delete (*it);
    }

    // delete all commands
    for (std::map<std::string, ft::Command *>::iterator it = _commands.begin(); it != _commands.end(); it++)
    {
        delete it->second;
    }
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
        if (servinfo)
            freeaddrinfo(servinfo);
        exit(1);
    }

    if ((this->master_fd = socket(servinfo->ai_family, servinfo->ai_socktype, servinfo->ai_protocol)) == -1)
    {
        std::cerr << "socket" << std::endl;
        if (servinfo)
            freeaddrinfo(servinfo);
        exit(1);
    }

    if (setsockopt(this->master_fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1)
    {
        std::cerr << "setsockopt" << std::endl;
        if (servinfo)
            freeaddrinfo(servinfo);
        exit(1);
    }

    if (bind(this->master_fd, servinfo->ai_addr, servinfo->ai_addrlen) == -1)
    {
        std::cerr << "bind" << std::endl;
        if (servinfo)
            freeaddrinfo(servinfo);
        exit(1);
    }

    if (listen(this->master_fd, 10) == -1)
    {
        std::cerr << "listen" << std::endl;
        if (servinfo)
            freeaddrinfo(servinfo);
        exit(1);
    }
    if (servinfo)
        freeaddrinfo(servinfo);
    std::cout << BCYN<< "Server listening on " << std::endl;
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
	storage.push_back("");

    // set timeout to 120 seconds
    const int timeout = 5 * 1000;
    std::cout << "Server is online" << DEFCOLO << std::endl;
    signal(SIGINT, sig_handler);
    while (1)
    {
        int ret = poll(&this->fds[0], this->fds.size(), timeout);
        if (ret == -1)
        {
            if (closeServer)
            {
                std::cout << "Closing server" << std::endl;
                break;
            }
            std::cerr << "poll" << std::endl;
            exit(1);
        }
        else if (ret == 0)
        {
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
		if (closeServer)
		{
			std::cout << "Closing server" << std::endl;
			break;
		}
		// VALGRIND_DO_LEAK_CHECK;
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
        std::cerr << "accept error" << std::endl;
        exit(1);
    }
    inet_ntop(their_addr.ss_family, get_in_addr((sockaddr *)&their_addr), ip_client, sizeof(ip_client));
    std::cout << "Create this client " << new_fd << std::endl;
    this->clients.push_back(new ft::Client(new_fd, servername, ip_client));
    pollfd pfd = {new_fd, POLLIN, 0};
    fds.push_back(pfd);
	storage.push_back("");
    std::cout << "💬 New connection from " << ip_client << " on socket " << new_fd << std::endl;
}

int	ft::Server::getClientInfoPos(int FDpos)
{
	for (size_t i = 0; i < clients.size(); i++)
	{
		if (clients[i]->fd == fds[FDpos].fd)
			return (i);	
	}
	return (FDpos - 1);
}

int	isCarriage(std::string arg)
{
	for (size_t i = 0; i < arg.size(); i++)
	{
		if (!std::isprint(arg[i]) && (int)arg[i] != 1)
			return (1);
	}
	return (0);
}

void	ft::Server::registerClient(Client *client)
{
	if (client->PASSFlag == 1 && client->NICKflag == 1 && client->USERflag == 1)
	{
		if (client->ALREADYREGISTERED == 0)
		{
			std::string msg = RPL_WELCOME(getServerName(), client->getNickName());
			sendReply(client, msg);
			msg = RPL_YOURHOST(getServerName(), client->getNickName(), getVersion());
			sendReply(client, msg);
			msg = RPL_CREATED(getServerName(), client->getNickName());
			sendReply(client, msg);
			msg = RPL_MYINFO(getServerName(), client->getNickName(), getVersion(), "User modes: ov", "Channel modes: imtlk");
			sendReply(client, msg);
			client->ALREADYREGISTERED = 1;
		}
	}
}

/**
 * @brief Receive message from client
 */
void ft::Server::receiveMessage(int i)
{
    int nbytes;
    char buf[1024] = {0};
    nbytes = recv(fds[i].fd, buf, 1024, 0);
    if (nbytes <= 0)
    {
		// ! remove a disconnected client in all cases it's gone forever
        std::cout << "🛑 Client " << clients[getClientInfoPos(i)]->getNickName() << " disconnected" << std::endl;
        remove_fds(fds[i].fd);
        removeClient(clients[getClientInfoPos(i)]);
        return;
    }
    else
    {
        buf[nbytes] = '\0';
        if (!strchr(buf, '\n'))
        {
            storage[i] += buf;
        }
        else
        {
            storage[i] += buf;
            std::vector<Message *> args = ft::Server::splitMessage(storage[i], '\n', fds[i].fd);
			if (args.size() < 1)
            {
				this->clients[getClientInfoPos(i)]->sendReply("ERROR :Unknown command\r");
                std::cout << BRED << "Unknown command" << DEFCOLO << std::endl;
			}
            for (size_t k = 0; k < args.size(); k++)
            {
                std::map<std::string, Command *>::iterator it;
                if ((it = _commands.find(args[k]->getCommand())) != _commands.end() && !isCarriage(args[k]->getmsg()))
                {
					if (args[k]->getCommand() == "PASS" || args[k]->getCommand() == "NICK" || args[k]->getCommand() == "USER" || args[k]->getCommand() == "CAP" || \
					(getClientInfoPos(i) < (int)this->clients.size() && this->clients[getClientInfoPos(i)]->ALREADYREGISTERED == 1))
					{
						
						Command *cmd = it->second;
						cmd->setClient(this->clients[getClientInfoPos(i)]);
						cmd->setServer(this);
						cmd->setMessage(args[k]);
						cmd->execute();
					}
					else
					{
						if (getClientInfoPos(i) < (int)this->clients.size())
                   			this->clients[getClientInfoPos(i)]->sendReply("ERROR :You are not fully registered\r");
					}
                    delete args[k];
                    args[k] = NULL;
                }
                else
                {
                    std::cout << BRED << "Unknown command" << DEFCOLO << std::endl;
					if (getClientInfoPos(i) < (int)this->clients.size())
                    	this->clients[getClientInfoPos(i)]->sendReply("ERROR :Unknown command\r");
                    delete args[k];
                    args[k] = NULL;
                }
            }
			if ((int)storage.size() > i)
				storage[i] = "";
            for (size_t k = 0; k < args.size(); k++)
            {
                if (args[k] != NULL)
                    delete args[k];
                args.erase(args.begin() + k);
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
    _commands["CAP"] = new ft::Cap();
    _commands["MODE"] = new ft::Mode();
    _commands["PING"] = new ft::Ping();
    _commands["PONG"] = new ft::Pong();
    _commands["PART"] = new ft::Part();
    _commands["PRIVMSG"] = new ft::Privmsg();
    _commands["NOTICE"] = new ft::Notice();
    _commands["INVITE"] = new ft::Invite();
    _commands["TOPIC"] = new ft::Topic();
    _commands["LIST"] = new ft::List();
    _commands["QUIT"] = new ft::Quit();
    _commands["PASS"] = new ft::Pass();
}

int		isMsgParsed(std::string msg)
{
	if (msg.size() == 1 && msg[0] == '\n')
		return (0);
	for (size_t i = 0; i < msg.size(); i++)
	{
		if (((int)msg[i] > 0 && (int)msg[i] < 32) && (int)msg[i] > 126)
		{
			if ((int)msg[i] != 13 && (int)msg[i] != 10)
				return (0);
		}
	}
	return (1);
}

/**
 * @brief split Message by newlines to to be multiple messages
 */

std::vector<ft::Message *> ft::Server::splitMessage(std::string msg, char delim, int fd)
{
    std::vector<ft::Message *> messages;
    std::stringstream ss(msg);
    std::string item;
	if (!isMsgParsed(msg))
		return (messages);
    while (std::getline(ss, item, delim))
    {
		if (strchr(item.c_str(), '\r'))
       		item = item.substr(0, item.size() - 1);
       	ft::Message *message = new ft::Message(item, fd);
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

bool ft::Server::isNickNameTaken(std::string nickname, Client *client)
{
    for (size_t i = 0; i < this->clients.size(); i++)
    {
        //send pong to the client
        if (this->clients[i]->getNickName() == nickname)
        {
            this->clients[i]->sendReply("PING :" + this->clients[i]->getNickName() + "\r");
            //set timeout
            struct timeval tv;
            tv.tv_sec = 3;
            tv.tv_usec = 0;
            setsockopt(this->clients[i]->fd, SOL_SOCKET, SO_RCVTIMEO, (const char *)&tv, sizeof(tv));
            char buf[1024];
            int nybtes = recv(this->clients[i]->fd, buf, sizeof(buf), 0);
            if (nybtes <= 0)
            {
                std::cout << "🔵 Client " << this->clients[i]->getNickName() << " is back" << std::endl;
                remove_fds(this->clients[i]->fd);
				resetFD(this->clients[i], client);
				client = NULL;
				CLIENTISBACK = true;
                return false;
            }
            {
                return true;
            }
        }
    }
    return false;
}

std::string ft::Server::getVersion()
{
    return this->version;
}

bool ft::Server::isChannel(std::string CHname)
{
    for (long unsigned int i = 0; i < this->channels.size(); i++)
    {
        if (this->channels[i]->getChName() == CHname)
            return (true);
    }
    return (false);
}

ft::Channel *ft::Server::getChannel(std::string CHname)
{
    for (long unsigned int i = 0; i < this->channels.size(); i++)
    {
        if (this->channels[i]->getChName() == CHname)
        	return (this->channels[i]);
    }
    return (NULL);
}

void	ft::Server::resetFD(Client *OLDclient, Client *NEWclient)
{
	OLDclient->fd = NEWclient->fd;
	CLIENTBACKFD = NEWclient->fd;
	for (size_t i = 0; i < this->clients.size(); i++)
    {
		// ! removing the new client that was added to the vector for checking and connecting processes
        if (this->clients[i] == NEWclient)
        {
            delete this->clients[i];
            this->clients[i] = NULL;
            this->clients.erase(this->clients.begin() + i);
        }
    }
}

void ft::Server::removeClient(Client *client)
{
	std::cout << BGRN << "Remmove the client " << client->fd << DEFCOLO << std::endl;
    for (size_t i = 0; i < this->clients.size(); i++)
    {
        if (this->clients[i] == client)
        {
			for (size_t k = 0; k < this->channels.size(); k++)
			{
				if (this->channels[k]->isMember(this->clients[i]->getNickName()))
					this->channels[k]->removeUser(this->clients[i]->getNickName());
			}
            delete this->clients[i];
            this->clients[i] = NULL;
            this->clients.erase(this->clients.begin() + i);
        }
    }
}

void ft::Server::remove_fds(int fd)
{
    close(fd);
    for (size_t i = 0; i < this->fds.size(); i++)
    {
        if (this->fds[i].fd == fd)
        {
            this->fds.erase(this->fds.begin() + i);
			this->storage.erase(this->storage.begin() + i);
        }
    }
}
