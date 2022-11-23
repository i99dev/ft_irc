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
#include <vector>

int main()
{
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0)
    {
        std::cout << "Error creating socket" << std::endl;
        return 1;
    }

    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(1234);
    //bind 
    if (bind(sock, (sockaddr*)&addr, sizeof(addr)) < 0)
    {
        std::cout << "Error binding socket" << std::endl;
        return 1;
    }

    //listen
    if (listen(sock, 1) < 0)
    {
        std::cout << "Error listening on socket" << std::endl;
        return 1;
    }

    //accept
    std::vector<struct pollfd> fds;
    struct pollfd fd;
    fd.fd = sock;
    fd.events = POLLIN;
    fds.push_back(fd);
    while (true)
    {
        int ret = poll(fds.data(), fds.size(), -1);
        if (ret < 0)
        {
            std::cout << "Error polling" << std::endl;
            return 1;
        }
        for (int i = 0; i < fds.size(); i++)
        {
            if (fds[i].revents & POLLIN)
            {
                if (fds[i].fd == sock)
                {
                    sockaddr_in client_addr;
                    socklen_t client_addr_size = sizeof(client_addr);
                    int client_sock = accept(sock, (sockaddr*)&client_addr, &client_addr_size);
                    if (client_sock < 0)
                    {
                        std::cout << "Error accepting client" << std::endl;
                        return 1;
                    }
                    struct pollfd fd;
                    fd.fd = client_sock;
                    fd.events = POLLIN;
                    fds.push_back(fd);
                }
                else
                {
                    char buf[1024];
                    int bytes = recv(fds[i].fd, buf, 1024, 0);
                    if (bytes < 0)
                    {
                        std::cout << "Error receiving data" << std::endl;
                        return 1;
                    }
                    if (bytes == 0)
                    {
                        close(fds[i].fd);
                        fds.erase(fds.begin() + i);
                        i--;
                        continue;
                    }
					send(fds[i].fd, ":ft_irc 001 sasori :Welcome to the Internet Relay Network sasori!sasori@127.0.0.1\r\n",168, 0); 
                    std::cout << "Received: " << std::string(buf, 0, bytes) << std::endl;
                }
            }
        }
    }
    return 0;
}