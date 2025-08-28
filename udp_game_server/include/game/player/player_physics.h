#ifndef PLAYER_PHYSICS_H
#define PLAYER_PHYSICS_H

#include "engine/constants/includes.h" 
#include "game/physics_manager.h"

class PlayerPhysics : public Component {
    PhysicsManager* physics;
    public:
    void Start();
    btCollisionWorld::ClosestConvexResultCallback SweepTest(btCollisionObject* collisionObject, btTransform startTransform, btTransform endTransform);
    std::vector<GameObject*> Raycast(Vector3 startPoint, Vector3 ray, float magnitude);
};

#endif