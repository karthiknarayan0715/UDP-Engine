#include <iostream>
#include <map>
#include "models/game/player.h"

class ClientMap {
    static std::map<std::string, Player> clientIdMap;
    public:
        static sockaddr* getClientSocket(std::string clientId) {
            return (sockaddr*) &clientIdMap[clientId].getClientSocket();
        }

        static void setClientData(std::string clientId, sockaddr_in clientSocket) {
            Player player = Player(clientId, clientSocket);
            clientIdMap[clientId] = player;
        }
};