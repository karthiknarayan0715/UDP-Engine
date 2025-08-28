#ifndef MAP_H
#define MAP_H

#include "engine/constants/includes.h"

class GameObject;

class Map {
    public:
    std::string name;
    std::vector<std::unique_ptr<GameObject>> gameObjects;
    Map(std::string string);
    void AddGameObjectToMap(std::unique_ptr<GameObject> object);
};

#endif