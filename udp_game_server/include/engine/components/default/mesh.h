#ifndef MESH_H
#define MESH_H

#include "engine/constants/includes.h"

using json = nlohmann::json;

class Mesh : public Component{
    public:
    std::vector<Vector3> vertices;
    std::vector<int> indices;

    Mesh() {}

    Mesh(json obj);

    std::unique_ptr<Component> Clone() const override;

    void LoadShape(json object);
    void LoadPlayer();
};

#endif