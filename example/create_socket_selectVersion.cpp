#include <stdio.h> 
#include <string.h>   //strlen 
#include <stdlib.h> 
#include <iostream>
#include <errno.h> 
#include <unistd.h>   //close 
#include <arpa/inet.h>    //close 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <sys/time.h> //FD_SET, FD_ISSET, FD_ZERO macros
#define PORT 8882
#define	MAXCLNT 10
#define	WLCMSG "Welcome to ft_irc_server \r\n"
#include <vector>
#include <algorithm>

class Server
{
	private:
		int					_masterSocket;
        int 				_opt;
   		struct sockaddr_in	_address;
		int					_addrlen;
		fd_set				_readfds; // fds set
    	int					_maxSocketfd; // will be used to define the range of the fds
		std::vector <int>	_clientSocket;
		int					_totalBitSet;
		int					_newSocket;
		int					_readbyte;
		char				_msgBuffer[1025];
	public:
		Server();
		~Server();
		int		creatSocket();
		int		bindSocket();
		void	resetClients();
		int		connectClients();
		void	getClientMsg();
};

Server::Server()
{
	this->_masterSocket = 0;
	this->_opt = 1;
	this->_address.sin_family = AF_INET;  
    this->_address.sin_addr.s_addr = INADDR_ANY;  
    this->_address.sin_port = htons(PORT);
    this->_addrlen = sizeof(this->_address);
}

int	Server::creatSocket()
{
	// create a socket for a server
	if (!(this->_masterSocket = socket(AF_INET , SOCK_STREAM , 0)))  
    {
		std::cout << "Socket: " << strerror(errno) << std::endl;
		return (0);
    }
	// /*
	// 	! optional to add
	// */
    // if (setsockopt(this->_masterSocket, SOL_SOCKET, SO_REUSEADDR, (char *)&this->_opt, sizeof(this->_opt)) < 0)  
    // {
	// 	std::cout << "Setsockopt: " << strerror(errno) << std::endl;
	// 	return (0);
    // }
	return (1);
}

int	Server::bindSocket()
{
	// * bind the socket to the the address (localhost) and to the port  
	if (bind(this->_masterSocket, (struct sockaddr *)&this->_address, sizeof(this->_address)) < 0)  
    {
		std::cout << "Bind: " << strerror(errno) << std::endl;
		return (0);
	}
	std::cout << "Listener on port " << PORT << std::endl;
	/*
	make server waits for the client connect
	define the length of queue of pending connection for the server
	if a connection request arrives when the queue is full, the client will be rejected 
	*/
	if (listen(this->_masterSocket, 1) < 0) 
    {
		std::cout << "Listen: " << strerror(errno) << std::endl;
		return (0);
    }
	return (1);
}

void	Server::resetClients()
{
	// clear the fds from the set, used to initialize the fds set
	FD_ZERO(&this->_readfds);
	// adding server socket to the set
	FD_SET(this->_masterSocket, &this->_readfds);
	// adding client's socket fds to the set
	for (std::vector<int>::iterator it = this->_clientSocket.begin(); it != this->_clientSocket.end(); it++)
		FD_SET(*it, &this->_readfds);
	// geting the max fd
	if (!this->_clientSocket.empty())
		this->_maxSocketfd = *max_element(this->_clientSocket.begin(), this->_clientSocket.end());
	else
		this->_maxSocketfd = this->_masterSocket;
}

int	Server::connectClients()
{
	// indicate which of the specified fds is ready to reading
	if (((this->_totalBitSet = select(this->_maxSocketfd + 1, &this->_readfds, NULL, NULL, NULL)) < 0) && (errno != EINTR))
		std::cout << "Select: " << strerror(errno) << std::endl;
	// if the fd is still in the set
	if (FD_ISSET(this->_masterSocket, &this->_readfds))
	{
		// extract the 1st connection request on the queue of the pending connection for the listening socket
		// create a new connected socket and return its fd
		if ((this->_newSocket = accept(this->_masterSocket, (struct sockaddr *)&this->_address, (socklen_t*)&this->_addrlen)) < 0)  
		{
			std::cout << "Accept: " << strerror(errno) << std::endl;
			return (0);
		}
		std::cout << "New connection: socket fd is " << this->_newSocket << ", ip address is " << inet_ntoa(this->_address.sin_addr) << ", port is" << ntohs(this->_address.sin_port) << std::endl;
		// send a welcome message to the connected socket
		if (send(this->_newSocket, WLCMSG, strlen(WLCMSG), 0) != strlen(WLCMSG))
			std::cout << "Send: " << strerror(errno) << std::endl;
		std::cout << "Welcome message sent successfully" << std::endl;
		// add the connected socket to the client list
		this->_clientSocket.push_back(this->_newSocket);
		std::cout << "Adding to list of sockets as " << this->_clientSocket.size() - 1 << std::endl;
	}
	return (1);
}

void	Server::getClientMsg()
{
	for (std::vector<int>::iterator clientFD = this->_clientSocket.begin(); clientFD != this->_clientSocket.end(); clientFD++)  
	{
		if (FD_ISSET(*clientFD, &this->_readfds))  
		{
			// read the message recieved
			if ((this->_readbyte = read(*clientFD, this->_msgBuffer, 1024)) == 0)  
			{
				// assign the address if the peer connected to the socket(_clientSocket[i]) in the buffer pointed to by adress
				getpeername(*clientFD, (struct sockaddr*)&this->_address, (socklen_t*)&this->_addrlen);  
				std::cout << "Disconnection: socket fd is " << *clientFD << ", ip address is " << inet_ntoa(this->_address.sin_addr) << ", port is" << ntohs(this->_address.sin_port) << std::endl;
				close(*clientFD);
				this->_clientSocket.erase(clientFD);
			}
			else 
			{
				// print the message received
				this->_msgBuffer[this->_readbyte] = '\0';
				std::cout << "Received: " << this->_msgBuffer << std::endl;
				std::string msg ("Server received this message: ");
				msg += this->_msgBuffer;
				// send message to the client 
				send(*clientFD, msg.c_str(), msg.length(), 0);
			}
		}  
	}
}

Server::~Server(){}

int main(int argc , char *argv[])  
{
	Server	server;
	if (!server.creatSocket())
		return (1);
	if (!server.bindSocket())
		return (1);
	std::cout << "Waiting for connections ..." << std::endl;
	while (true)
	{
		server.resetClients();
		if (!server.connectClients())
			return (1);
		server.getClientMsg();
	}
    return (0);  
}