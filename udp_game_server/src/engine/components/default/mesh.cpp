#include "engine/components/default/mesh.h"
#include "engine/game_object/game_object.h"
#include "engine/components/default/transform.h"

using json = nlohmann::json;

Mesh::Mesh(json object) {
    this->LoadShape(object);
}

void Mesh::LoadShape(json object) {
    if(this->gameObject == nullptr) {
        spdlog::error("In LoadShape, the component's gameobject is null");
        return;
    }
    if(this->gameObject->GetComponent<Transform>() == nullptr) {
        spdlog::error("In LoadShape, the component gameobject's transform is null");
        return;
    }
    for (const auto& vert : object["meshVertices"]) {
        Vector3 adjustedVertex = Vector3(
            vert["x"].get<float>(),
            vert["y"].get<float>(),
            vert["z"].get<float>()
        );
        this->vertices.push_back(adjustedVertex);
    }        

    for (const auto& idx : object["meshTriangles"]) {
        this->indices.push_back(idx);
    }
}

void Mesh::LoadPlayer() {
    std::ifstream file("static/colliders/player.json");
    if (!file.is_open()) {
        spdlog::error("Error loading player collider: {}", std::strerror(errno));
        return;
    }
    json jsonData;
    file >> jsonData;
    file.close();
    this->LoadShape(jsonData["objects"][0]);
}

std::unique_ptr<Component> Mesh::Clone() const {
    std::unique_ptr<Mesh> new_mesh = std::make_unique<Mesh>();
    new_mesh->indices = this->indices;
    new_mesh->vertices = this->vertices;
    return new_mesh;
}