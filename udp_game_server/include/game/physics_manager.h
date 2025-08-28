#ifndef PHYSICS_MANAGER_H
#define PHYSICS_MANAGER_H

#include "engine/constants/includes.h"
#include "game/map.h"

class PhysicsManager {
    std::string game_id;
    std::unique_ptr<btBroadphaseInterface> broadphase;
    std::unique_ptr<btDefaultCollisionConfiguration> collisionConfiguration;
    std::unique_ptr<btCollisionDispatcher> dispatcher;
    public:
    std::unique_ptr<btCollisionWorld> collisionWorld;
    std::unique_ptr<Map> map;
    Game* game;
    PhysicsManager() {}
    PhysicsManager(std::string game_id);
    std::unique_ptr<Map> CloneGlobalMap(Map* map);
    void AddCollisionObjectToWorld(btCollisionObject* object);
    void LoadMap(std::string map);
    btCollisionWorld::ClosestConvexResultCallback ConvexSweepTest(btCollisionObject* collisionObject, btTransform startTransform, btTransform endTransform);
    std::vector<GameObject*> Raycast(btVector3 startPoint, btVector3 ray, float magnitude);
};

#endif