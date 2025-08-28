#include "models/game/inputs/player_inputs_request.h"

PlayerInputsRequest::PlayerInputsRequest(std::string inputsRequest) {
    std::vector<std::string> splitRequest = split(inputsRequest, FIELD_SEPERATOR);
    this->moveX = std::stof(splitRequest[0]);
    this->moveZ = std::stof(splitRequest[1]);
    this->playerRotation = Vector3(splitRequest[2]);
    this->cameraRotation = Vector3(splitRequest[3]);
    this->isJumping = std::stoi(splitRequest[4]);
    this->isShooting = std::stoi(splitRequest[5]);
}