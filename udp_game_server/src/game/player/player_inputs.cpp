#include "game/player/player_inputs.h"
#include "models/game/inputs/player_inputs_request.h"

PlayerInputs::PlayerInputs(PlayerInputsRequest playerInputsRequest) {
    this->UpdateInputs(playerInputsRequest);
}

void PlayerInputs::UpdateInputs(PlayerInputsRequest playerInputsRequest) {
    this->moveX = playerInputsRequest.moveX;
    this->moveZ = playerInputsRequest.moveZ;
    this->playerRotation = playerInputsRequest.playerRotation;
    this->cameraRotation = playerInputsRequest.cameraRotation;
    this->isJumping = this->isJumping || playerInputsRequest.isJumping;
    this->isShooting = this->isShooting || playerInputsRequest.isShooting;
}