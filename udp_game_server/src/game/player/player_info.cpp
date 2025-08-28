#include "game/player/player_info.h"
#include "game/player/player_health.h"
#include "game/player/player_camera.h"
#include "engine/game_object/game_object.h"
#include "engine/components/default/transform.h"
#include "server/server.h"

PlayerInfo::PlayerInfo(sockaddr_in clientSocket, std::string clientId, Vector3 speed) {
    this->speed = speed;
    this->clientId = clientId;
    this->clientSocket = clientSocket;
}

std::string PlayerInfo::ToString() {
    Transform* transform = this->gameObject->GetComponent<Transform>();
    return this->clientId + ":" + transform->position.ToString() + "|" + this->speed.ToString() + "|" + transform->rotation.ToString() + "|" + this->gameObject->GetComponent<PlayerCamera>()->rotation.ToString() + "|" + std::to_string(this->gameObject->GetComponent<PlayerHealth>()->GetHealth());
}

sockaddr_in PlayerInfo::getClientSocket() {
    return this->clientSocket;
}