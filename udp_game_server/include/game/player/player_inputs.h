#ifndef PLAYER_INPUTS_H
#define PLAYER_INPUTS_H

#include "engine/constants/includes.h"

class PlayerInputsRequest;

class PlayerInputs : public Component {
    public:
    int moveX, moveZ;
    Vector3 playerRotation;
    Vector3 cameraRotation;
    bool isJumping;
    bool isShooting;
    PlayerInputs(PlayerInputsRequest playerInputsRequest);
    void UpdateInputs(PlayerInputsRequest playerInputsRequest);
};

#endif