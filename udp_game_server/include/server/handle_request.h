#include<iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

class Request;

void HandleRequest(sockaddr_in clientSocket, Request request);