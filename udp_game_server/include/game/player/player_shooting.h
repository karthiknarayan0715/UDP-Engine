#ifndef PLAYER_SHOOTING_H
#define PLAYER_SHOOTING_H

#include "engine/constants/includes.h"

class PlayerShooting : public Component {
    public:
    void Update();
    void Shoot(); 
};

#endif