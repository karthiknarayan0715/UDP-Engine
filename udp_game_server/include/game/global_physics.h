#ifndef GLOBAL_PHYSICS_H
#define GLOBAL_PHYSICS_H

#include "engine/constants/includes.h"
#include "game/map.h"

typedef struct {
    std::string path;
    bool isMap;
} MeshInfoModel;

using json = nlohmann::json;

extern std::map<std::string, std::unique_ptr<Map>> global_map_data;

const std::map<std::string, MeshInfoModel> collider_info = {
    {"player", {"colliders/player.json", false}},
    {"map_collider", {"map/map.json", true}}
};

void LoadMaps();

#endif