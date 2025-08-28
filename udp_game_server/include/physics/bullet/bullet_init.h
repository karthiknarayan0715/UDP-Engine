// #ifndef BULLET_INIT_H
// #define BULLET_INIT_H

// #include <memory>
// #include <vector>
// #include <btBulletCollisionCommon.h>

// #include "physics/models/map_object.h"
// #include "physics/bullet/handler.h"

// class GameObject;

// struct ObjectInfo {
//     std::string path;
//     bool isMap;
// };

// const std::map<std::string, ObjectInfo> collider_paths = {
//     {"player", {"colliders/player.json", false}},
//     {"map_collider", {"map/map.json", true}}
// };

// class CollisionResultCallback : public btCollisionWorld::ContactResultCallback {
//     public:
//         bool collisionDetected = false;
    
//         virtual btScalar addSingleResult([[maybe_unused]] btManifoldPoint& cp,
//                                  [[maybe_unused]] const btCollisionObjectWrapper* colObj0Wrap, 
//                                  [[maybe_unused]] int partId0, [[maybe_unused]] int index0,
//                                  [[maybe_unused]] const btCollisionObjectWrapper* colObj1Wrap, 
//                                  [[maybe_unused]] int partId1, [[maybe_unused]] int index1) override {
//             collisionDetected = true;

//             return 0;
//         }
//     };
    

// class BulletPhysics{
    // std::shared_ptr<btBroadphaseInterface> broadphase;
    // std::shared_ptr<btDefaultCollisionConfiguration> collisionConfiguration;
    // std::shared_ptr<btCollisionDispatcher> dispatcher;
    // std::shared_ptr<btCollisionWorld> collisionWorld;

//     std::map<int, std::shared_ptr<btConvexHullShape>> loadedColliders;
//     std::map<int, std::shared_ptr<btCollisionObject>> loadedColliderObjects;
//     std::map<int, std::shared_ptr<GameObject>> loadGameObjectsMapped;

//     std::map<std::string, std::shared_ptr<GameObject>> loadedGameObjects;
//     std::map<std::string, MapObject> loadedMapObjects;

//     int collider_index = 0;
    
//     void LoadMapGameObjects();

//     public:
//     BulletPhysics(const BulletPhysics&) = delete;
//     BulletPhysics& operator=(const BulletPhysics&) = delete;

//     static BulletPhysics& GetInstance() {
//         static BulletPhysics Instance;
//         return Instance;
//     }
    
//     BulletPhysics();
//     std::shared_ptr<GameObject> LoadPlayer();
//     bool CheckCollision(std::shared_ptr<btCollisionObject> objA, std::shared_ptr<btCollisionObject> objB);
//     void Init();
//     std::shared_ptr<GameObject> AddPlayerGameObject();
//     std::vector<std::shared_ptr<GameObject>> GetCollisions(std::shared_ptr<GameObject> self);
//     std::vector<std::shared_ptr<GameObject>> Raycast(std::shared_ptr<GameObject> self, btVector3 ray, float magnitude, btVector3 startPointOffset = btVector3(0, 0, 0));
//     std::shared_ptr<GameObject> GetGameObjectFromId(int collider_id);
//     btCollisionWorld::ClosestConvexResultCallback CollideAndSlideCollisionCheck(std::shared_ptr<GameObject> self, btTransform startTransform, btTransform endTransform);

// };

// class RayCastResultCallback : public btCollisionWorld::RayResultCallback {
//     public:
//         std::vector<std::shared_ptr<GameObject>> gameObjects;

//         virtual btScalar addSingleResult(btCollisionWorld::LocalRayResult& rayResult, [[maybe_unused]] bool normalInWorldSpace) override {
//             std::shared_ptr<GameObject> gameObject = BulletPhysics::GetInstance().GetGameObjectFromId(((GameObject*)rayResult.m_collisionObject->getUserPointer())->collider_index);
//             gameObjects.push_back(gameObject);
//             return 0;
//         }
// };

// #endif