#include "game/map.h"

Map::Map(std::string name) {
    this->name = name;
}

void Map::AddGameObjectToMap(std::unique_ptr<GameObject> object) {
    this->gameObjects.push_back(std::move(object));
}