#ifndef PLAYER_CAMERA_H
#define PLAYER_CAMERA_H

#include "engine/constants/includes.h"

class Component;

class PlayerCamera : public Component {
    public:
    Vector3 rotation;
    PlayerCamera(Vector3 cameraRotation);
};

#endif