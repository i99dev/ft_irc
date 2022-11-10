# include <sys/socket.h>
# include <sys/types.h>
# include <netinet/in.h>
# include <iostream>
# include <unistd.h>
# include <string.h>


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
    int client = accept(sock, NULL, NULL);
    if (client < 0)
    {
        std::cout << "Error accepting connection" << std::endl;
        return 1;
    }

    //send
    const char* msg = "Hello from server";
    int sendRes = send(client, msg, strlen(msg), 0);
    if (sendRes < 0)
    {
        std::cout << "Error sending message" << std::endl;
        return 1;
    }

    //close
    close(client);
    close(sock);

    return 0;
}
