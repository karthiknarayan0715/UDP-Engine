#ifndef SERVER_H
#define SERVER_H

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>
#include <cstring>
#include <thread>


class Server {
private:
    Server(){}
public:
    int serverSocket;

    Server(const Server&) = delete;
    Server& operator=(const Server&) = delete;

    static Server& getInstance() {
        static Server Instance;
        return Instance;
    }
    
    int Start();

    void ListenForMessages();

    void SendMessage(sockaddr_in clientAddress, std::string message);
};

#endif