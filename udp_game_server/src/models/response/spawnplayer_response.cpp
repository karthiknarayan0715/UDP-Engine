#include "models/response/spawnplayer_response.h"
#include <string>
#include <sstream>

SpawnPlayerResponse::SpawnPlayerResponse(Vector3 position, std::string _clientId) {
    spawn_point = position;
    this->clientId = _clientId;
}

std::string SpawnPlayerResponse::GetMessage() {
    std::ostringstream response;
    response << clientId << "|" << spawn_point.ToString();
    return response.str();
}