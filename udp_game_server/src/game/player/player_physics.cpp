#include "game/player/player_physics.h"
#include "game/physics_manager.h"
#include "game/game.h"

void PlayerPhysics::Start() {
    this->physics = this->gameObject->game->physics.get();
}

btCollisionWorld::ClosestConvexResultCallback PlayerPhysics::SweepTest(btCollisionObject* collisionObject, btTransform startTransform, btTransform endTransform) {
    return this->physics->ConvexSweepTest(collisionObject, startTransform, endTransform);
}

std::vector<GameObject*> PlayerPhysics::Raycast(Vector3 startPoint, Vector3 ray, float magnitude) {
    std::vector<GameObject*> hitObjects;
    std::vector<GameObject*> physicsRaycastResult = this->physics->Raycast(Vector3::getBtVector3(startPoint), Vector3::getBtVector3(ray), magnitude);
    for (GameObject* object : physicsRaycastResult) {
        if (object != this->gameObject) {
            hitObjects.push_back(object);
        }
    }
    return hitObjects;
}