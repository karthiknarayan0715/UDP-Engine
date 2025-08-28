#ifndef PLAYER_INPUTS_REQUEST_H
#define PLAYER_INPUTS_REQUEST_H

#include "utils/vector3/vector3.h"
#include "models/constants/constants.h"

class PlayerInputsRequest {
    public:
    int moveX, moveZ;
    Vector3 playerRotation;
    Vector3 cameraRotation;
    bool isJumping;
    bool isShooting;
    PlayerInputsRequest(){}
    PlayerInputsRequest(std::string inputsRequest);
};

#endif