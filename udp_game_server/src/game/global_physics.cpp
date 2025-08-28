#include "game/global_physics.h"
#include "engine/game_object/game_object.h"
#include "engine/components/default/mesh.h"
#include "engine/components/default/mesh_collider.h"

std::map<std::string, std::unique_ptr<Map>> global_map_data;

void LoadMaps() {
    for (auto it = collider_info.begin(); it != collider_info.end(); ++it) {
        if (!it->second.isMap) continue;
        spdlog::info("Loading Map: {}", it->first);
        std::unique_ptr<Map> map = std::make_unique<Map>(it->first);
        std::ifstream file("static/" + it->second.path);
        if (!file.is_open()) {
            spdlog::error("Error loading map {}: {}", it->first, std::strerror(errno));
            return;
        }
        json jsonData;
        file >> jsonData;
        file.close();
        for (const auto& obj : jsonData["objects"]) {
            Vector3 position = {obj["position"]["x"], obj["position"]["y"], obj["position"]["z"]};
            Vector3 rotation = {obj["rotation"]["x"], obj["rotation"]["y"], obj["rotation"]["z"]};
            Vector3 scale = {obj["scale"]["x"], obj["scale"]["y"], obj["scale"]["z"]};
            std::unique_ptr<GameObject> game_object = std::make_unique<GameObject>(position, rotation, scale);
            game_object->name = obj["name"];
            game_object->AddComponent<Mesh>(std::make_unique<Mesh>());
            game_object->GetComponent<Mesh>()->LoadShape(obj);
            game_object->AddComponent<MeshCollider>(std::make_unique<MeshCollider>(game_object->GetComponent<Mesh>()));
            spdlog::debug("Mesh name: {}, Vertex count: {}", game_object->name, game_object->GetComponent<Mesh>()->vertices.size());
            map->AddGameObjectToMap(std::move(game_object));
        }
        global_map_data.insert_or_assign(it->first, std::move(map));
    }

    spdlog::info("Finished loading maps. Maps loaded: {}", global_map_data.size());
}