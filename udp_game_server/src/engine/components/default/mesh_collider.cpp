#include "engine/components/default/mesh_collider.h"
#include "engine/components/default/mesh.h"
#include "engine/components/default/transform.h"
#include "game/game.h"
#include "game/physics_manager.h"
#include "game/player/player_info.h"
#include "game/player/player_physics.h"

MeshCollider::MeshCollider(Mesh* mesh) {
    this->convexHullShape = std::make_unique<btConvexHullShape>();
    this->convexHullShape->setMargin(0.0);
    for (Vector3 point : mesh->vertices) {
        this->convexHullShape->addPoint(Vector3::getBtVector3(point));
    }
    this->convexHullShape->recalcLocalAabb();
    this->collisionObject = std::make_unique<btCollisionObject>();
    this->collisionObject->setCollisionShape(this->convexHullShape.get());
}

void MeshCollider::Start() {
    this->collisionObject->setWorldTransform(GetCurrentWorldTransform());
    this->collisionObject->setUserPointer(this->gameObject);
    this->gameObject->game->physics->AddCollisionObjectToWorld(this->collisionObject.get());
}

btTransform MeshCollider::GetCurrentWorldTransform() {
    Transform* transform = this->gameObject->GetComponent<Transform>();
    if (transform == nullptr) return btTransform();
    btTransform bt_transform = btTransform();
    bt_transform.setIdentity();
    bt_transform.setOrigin(btVector3(transform->position.x, transform->position.y, transform->position.z) + Vector3::getBtVector3(this->offset));
    return bt_transform;
}

btTransform MeshCollider::GetCustomTransformFromVector3(Vector3 position) {
    btTransform bt_transform = btTransform();
    bt_transform.setIdentity();
    bt_transform.setOrigin(btVector3(position.x, position.y, position.z) + Vector3::getBtVector3(this->offset));
    return bt_transform;
}

std::unique_ptr<Component> MeshCollider::Clone() const {
    Mesh* mesh = this->gameObject->GetComponent<Mesh>();
    std::unique_ptr<MeshCollider> new_mesh_collider = std::make_unique<MeshCollider>(mesh);
    return new_mesh_collider;
}

void MeshCollider::Update() {
    this->collisionObject->setWorldTransform(GetCurrentWorldTransform());
}

void MeshCollider::UpdateTransform() {
    this->collisionObject->setWorldTransform(GetCurrentWorldTransform());
}

btCollisionWorld::ClosestConvexResultCallback MeshCollider::CheckAnyNewCollisions(Vector3 oldTransform, Vector3 newTransform) {
    for (const std::unique_ptr<GameObject>& go : this->gameObject->game->map->gameObjects) {
        btCollisionObject* collisionObject = go->GetComponent<MeshCollider>()->collisionObject.get();
        if (collisionObject == nullptr) {
            spdlog::error("The collision object is null");
        }
        btConvexHullShape* shape = dynamic_cast<btConvexHullShape*>(collisionObject->getCollisionShape());
        if (shape == nullptr) {
            spdlog::error("The collision shape is null");
        }
    }
    return this->gameObject->GetComponent<PlayerPhysics>()->SweepTest(this->collisionObject.get(), GetCustomTransformFromVector3(oldTransform), GetCustomTransformFromVector3(newTransform));
}

void MeshCollider::SetOffset(Vector3 offset) {
    this->offset = offset;
}