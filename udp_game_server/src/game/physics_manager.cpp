#include "game/physics_manager.h"
#include "game/global_physics.h"
#include "engine/components/default/transform.h"

PhysicsManager::PhysicsManager(std::string game_id) {
    this->game_id = game_id;
    this->broadphase = std::make_unique<btDbvtBroadphase>();
    this->collisionConfiguration = std::make_unique<btDefaultCollisionConfiguration>();
    this->dispatcher = std::make_unique<btCollisionDispatcher>(collisionConfiguration.get());
    this->collisionWorld = std::make_unique<btCollisionWorld>(dispatcher.get(), broadphase.get(), collisionConfiguration.get());
}

void PhysicsManager::AddCollisionObjectToWorld(btCollisionObject* object) {
    this->collisionWorld->addCollisionObject(object);
}

std::unique_ptr<Map> PhysicsManager::CloneGlobalMap(Map* map) {
    std::unique_ptr<Map> new_map = std::make_unique<Map>(map->name);
    if (map == nullptr) {
        spdlog::error("param: map is null in CloneGlobalMap");
    }
    for (const std::unique_ptr<GameObject>& gameObject : map->gameObjects) {
        std::unique_ptr<GameObject> gameObject_cloned = gameObject->Clone();
        gameObject_cloned->game = this->game;
        spdlog::debug("GO Components: {}, Cloned GO Components: {}", gameObject->components.size(), gameObject_cloned->components.size()); 
        new_map->AddGameObjectToMap(std::move(gameObject_cloned));
    }
    return new_map;
}

void PhysicsManager::LoadMap(std::string map_name) {
    spdlog::debug("Looking for map: {}", map_name);
    auto it = global_map_data.find(map_name);
    if (it == global_map_data.end()) {
        spdlog::error("Could not find map provided to PhysicsManager");
        return;
    }
    Map* current_map = it->second.get();
    this->map = std::move(CloneGlobalMap(current_map));
    spdlog::info("Loading map {} to game: {}", map_name, game_id);
}

btCollisionWorld::ClosestConvexResultCallback PhysicsManager::ConvexSweepTest(btCollisionObject* collisionObject, btTransform startTransform, btTransform endTransform) {
    if (collisionObject == nullptr) {
        spdlog::error("The providded collsion object is null");
        return btCollisionWorld::ClosestConvexResultCallback(startTransform.getOrigin(), endTransform.getOrigin());;
    }

    btConvexShape* convexShape = dynamic_cast<btConvexShape*>(collisionObject->getCollisionShape());
    if (!convexShape) {
        spdlog::error("ConvexSweepTest failed: shape is not a btConvexShape!");
        return btCollisionWorld::ClosestConvexResultCallback(startTransform.getOrigin(), endTransform.getOrigin()); // return empty
    }
    this->collisionWorld->removeCollisionObject(collisionObject);

    btCollisionWorld::ClosestConvexResultCallback hitCallback(startTransform.getOrigin(), endTransform.getOrigin());

    this->collisionWorld->convexSweepTest(convexShape, startTransform, endTransform, hitCallback);

    this->collisionWorld->addCollisionObject(collisionObject);

    return hitCallback;
}

std::vector<GameObject*> PhysicsManager::Raycast(btVector3 startPoint, btVector3 ray, float magnitude) {
    std::vector<GameObject*> hitObjects;
    btVector3 rayStart = startPoint;
    btVector3 rayEnd = rayStart + ray * magnitude;

    btCollisionWorld::AllHitsRayResultCallback rayCallback(rayStart, rayEnd);

    this->collisionWorld->rayTest(rayStart, rayEnd, rayCallback);

    if (rayCallback.hasHit()) {
        for (int i = 0; i < rayCallback.m_collisionObjects.size(); i++) {
            const btCollisionObject* hitObj = rayCallback.m_collisionObjects[i];
            GameObject* rawPointer = static_cast<GameObject*>(hitObj->getUserPointer());

            if (!rawPointer) {
                std::cout << "GameObject is nullptr at index: " << i << std::endl;
                continue;
            }
            GameObject* gameObject = rawPointer;
            
            if (gameObject) {
                hitObjects.push_back(gameObject);
            }
        }
    }

    return hitObjects;
}
