#ifndef PLAYER_UTILS_H
#define PLAYER_UTILS_H

#include "engine/constants/includes.h"

class PlayerUtils {
    public:
        static void AddDefaultComponentsToPlayer(std::unique_ptr<GameObject> player);
};

#endif