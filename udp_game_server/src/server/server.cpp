#include "string_utils/string_utils.h"
#include "models/request/request.h"
#include "models/constants/constants.h"
#include "models/constants/request_type_map.h"
#include "models/sql/mySqlConnector.h"
#include "game/game_loop.h"
#include "server/server.h"
#include "server/handle_request.h"

int Server::Start() {
    // Create socket
    this->serverSocket = socket(AF_INET, SOCK_DGRAM, 0);
    if (this->serverSocket == -1) {
        spdlog::error("Error: Socket Creation Failed");
        return 0;
    }

    // Configure server address
    sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(PORT);
    
    // Bind socket
    if (bind(this->serverSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) == -1) {
        spdlog::error("Error: Bind failed");
        close(this->serverSocket);
        return 0;
    }

    std::thread worker(GameLoop::StartGameLoop);

    spdlog::debug("Starting the server...");
    spdlog::info("UDP Server is running on port {}...", PORT);

    // std::cout << " " << PORT << "...\n";/

    this->ListenForMessages();
    return 1;
}

void Server::ListenForMessages() {
    char buffer[BUFFER_SIZE];
    sockaddr_in clientAddr;
    socklen_t clientAddrLen = sizeof(clientAddr);

    while (true) {
        int bytesReceived = recvfrom(this->serverSocket, buffer, BUFFER_SIZE, 0, 
                                     (sockaddr*)&clientAddr, &clientAddrLen);
        if (bytesReceived == -1) {
            std::cerr << "recvfrom failed\n";
            break;
        }

        if (bytesReceived > 0) {
            buffer[bytesReceived] = '\0';

            Request request = Request(buffer);
            
            HandleRequest(clientAddr, request);
        }
    }
}

void Server::SendMessage(sockaddr_in clientAddress, std::string message) {
    int bytesSent = sendto(this->serverSocket, message.c_str(), message.size(), 0, 
                           (sockaddr*)&clientAddress, sizeof(clientAddress));
    if (bytesSent == -1) {
        std::cerr << "sendto failed\n";
    }
}