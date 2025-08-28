#ifndef PLAYER_HEALTH_H
#define PLAYER_HEALTH_H

#include "engine/constants/includes.h"

class PlayerHealth : public Component {
    float health;
    public:
    void Start();
    float GetHealth();
    void TakeDamage(float damage);
};

#endif