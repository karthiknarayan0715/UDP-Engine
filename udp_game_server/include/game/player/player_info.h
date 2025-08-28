#ifndef PLAYER_INFO_H
#define PLAYER_INFO_H

#include "engine/constants/includes.h"
#include "server/server.h"

class Component;

class PlayerInfo : public Component {
    public:
    Vector3 speed;
    std::string clientId;
    sockaddr_in clientSocket;
    Vector3 player_center_offset = {0.0, 1.0, 0.0};
    PlayerInfo(sockaddr_in clientSocket, std::string clientId, Vector3 speed);
    std::string ToString();
    sockaddr_in getClientSocket();
};

#endif