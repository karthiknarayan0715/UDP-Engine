#ifndef PLAYER_CONSTANTS_H
#define PLAYER_CONSTANTS_H  

#include "engine/constants/includes.h"

class PlayerConstants : public Component {
    public:
    Vector3 playerBodyGroundOffset = {0.0, 1.0, 0.0};
    Vector3 groundCheckOffset = {0.0, 0.15, 0.0};
    Vector3 firstPersonCameraOffset = {0, 1.45, 0};

    float groundCheckDistance = 0.4;
    void Start();
};

#endif