#include "engine/game_object/game_object.h"
#include "engine/components/default/transform.h"
#include "engine/components/default/mesh.h"
#include "engine/components/default/mesh_collider.h"

GameObject::GameObject(Vector3 position, Vector3 rotation, Vector3 scale) {
    this->AddComponent<Transform>(std::make_unique<Transform>(position, rotation, scale));
}

void GameObject::Start() {
    for (auto it = this->components.begin(); it != this->components.end(); ++it) {
        it->second->Start();
    }
}

void GameObject::Update() { 
    for (auto it = this->components.begin(); it != this->components.end(); ++it) {
        it->second->Update();
    }
}

std::unique_ptr<GameObject> GameObject::Clone() {
    std::unique_ptr new_go = std::make_unique<GameObject>(this->GetComponent<Transform>()->position, this->GetComponent<Transform>()->rotation);
    new_go->name = this->name;
    if (this->GetComponent<Mesh>()){
        std::unique_ptr<Mesh> mesh_clone = std::unique_ptr<Mesh>(static_cast<Mesh*>(this->GetComponent<Mesh>()->Clone().release()));
        new_go->AddComponent<Mesh>(std::move(mesh_clone));
    }
    if (this->GetComponent<MeshCollider>()) {
        std::unique_ptr<MeshCollider> mesh_collider_clone = std::unique_ptr<MeshCollider>(static_cast<MeshCollider*>(this->GetComponent<MeshCollider>()->Clone().release()));
        new_go->AddComponent<MeshCollider>(std::move(mesh_collider_clone));
    }
    

    return new_go;
}