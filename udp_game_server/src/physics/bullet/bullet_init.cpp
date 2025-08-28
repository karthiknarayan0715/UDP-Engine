// #include "physics/bullet/bullet_init.h"
// #include "physics/models/game_object.h"

// BulletPhysics::BulletPhysics() {
//     this->broadphase = std::make_shared<btDbvtBroadphase>();
//     this->collisionConfiguration = std::make_shared<btDefaultCollisionConfiguration>();
//     this->dispatcher = std::make_shared<btCollisionDispatcher>(collisionConfiguration.get());
//     this->collisionWorld = std::make_shared<btCollisionWorld>(dispatcher.get(), broadphase.get(), collisionConfiguration.get());
// }

// void BulletPhysics::LoadMapGameObjects() {
//     for (auto it = collider_paths.begin(); it != collider_paths.end(); ++it) {
//         const std::string& name = it->first;
//         const ObjectInfo& info = it->second;
//         if (info.isMap) {
//             std::vector<MeshObject> mapMesh;
//             std::vector<std::shared_ptr<GameObject>> gameObjects;
//             if (LoadMeshFromJson(info.path, mapMesh)) {
//                 std::cout<<"Loaded Map " << name << " successfully!"<<std::endl;
//             }
//             else {
//                 std::cerr<<"Error loading map " << name <<"!"<<std::endl;
//             }
            
//             for (MeshObject mesh : mapMesh) {
//                 std::shared_ptr<GameObject> gameObject = std::make_shared<GameObject>(mesh);
//                 gameObject->setColliderIndex(this->collider_index);
//                 gameObjects.push_back(gameObject);
//                 loadGameObjectsMapped[this->collider_index] = gameObject;
//                 loadedColliders[this->collider_index] = mesh.getConvexHullShape();
//                 std::shared_ptr<btCollisionObject> collisionObject = std::make_shared<btCollisionObject>();
//                 collisionObject->setCollisionShape(loadedColliders[this->collider_index].get());
//                 this->collisionWorld->addCollisionObject(collisionObject.get());
//                 loadedColliderObjects[this->collider_index] = collisionObject;
//                 loadedColliderObjects[this->collider_index]->setUserPointer(gameObject.get());
//                 this->collider_index++;
//             }
//             loadedMapObjects[name] = MapObject(gameObjects);
//         }
//     }
// }

// std::shared_ptr<GameObject> BulletPhysics::LoadPlayer() {
//     MeshObject meshObject = MeshObject();
//     const std::string& name = "player";
//     const ObjectInfo& info = collider_paths.find(name)->second;
//     if (LoadObjectFromJson(info.path, meshObject)) {
//         // std::cout<<"Loaded Object " << name << " successfully!" << std::endl;
//         // std::cout<<"Loaded Points " << meshObject.getConvexHullShape()->getNumPoints() <<std::endl;
//     }
//     else {
//         std::cerr<<"Error loading Object " << name <<"!"<<std::endl;
//         return NULL;
//     }
//     std::shared_ptr<GameObject> gameObject = std::make_shared<GameObject>(meshObject);
//     gameObject->setColliderIndex(this->collider_index);
//     loadGameObjectsMapped[this->collider_index] = gameObject;
//     loadedColliders[this->collider_index] = meshObject.getConvexHullShape();
//     std::shared_ptr<btCollisionObject> collisionObject = std::make_shared<btCollisionObject>();
//     collisionObject->setCollisionShape(loadedColliders[this->collider_index].get());
//     this->collisionWorld->addCollisionObject(collisionObject.get());
//     loadedColliderObjects[this->collider_index] = collisionObject;
//     loadedColliderObjects[this->collider_index]->setUserPointer(gameObject.get());
//     this->collider_index++;
//     return gameObject;
// }

// bool BulletPhysics::CheckCollision(std::shared_ptr<btCollisionObject> objA, std::shared_ptr<btCollisionObject> objB) {
//     if (!objA || !objB) {
//         std::cerr << "Error: Null collision object passed!" << std::endl;
//         return false;
//     }
//     if (!objA->getCollisionShape() || !objB->getCollisionShape()) {
//         std::cerr << "Error: Null shape in collision objects!" << std::endl;
//         return false;
//     }

//     CollisionResultCallback result;
//     this->collisionWorld->contactPairTest(objA.get(), objB.get(), result);

//     return result.collisionDetected;
// }

// void BulletPhysics::Init() {
//     LoadMapGameObjects();
// }

// std::shared_ptr<GameObject> BulletPhysics::AddPlayerGameObject() {
//     std::shared_ptr<GameObject> playerGameObject = LoadPlayer();
//     return playerGameObject;
// }

// std::vector<std::shared_ptr<GameObject>> BulletPhysics::GetCollisions(std::shared_ptr<GameObject> self) {
//     if (loadedColliders.find(self->collider_index) == loadedColliders.end() || !loadedColliders[self->collider_index]) {
//         std::cerr << "Error: Collider index not found or is null for player!" << std::endl;
//         return {};
//     }
//     std::vector<std::shared_ptr<GameObject>> result;
//     std::shared_ptr<btConvexHullShape> player_shape = loadedColliders[self->collider_index];
//     std::shared_ptr<btCollisionObject> player_collision_object = std::make_shared<btCollisionObject>();
//     btTransform transform = btTransform();
//     transform.setOrigin(self->position);
//     transform.setRotation(btQuaternion(self->rotation.getX(), self->rotation.getY(), self->rotation.getZ()));
//     player_collision_object->setCollisionShape(player_shape.get());
//     player_collision_object->setWorldTransform(transform);
//     for (std::shared_ptr<GameObject> gameObject : loadedMapObjects["map_collider"].objects) {
//         if (loadedColliders.find(gameObject->collider_index) == loadedColliders.end() || !loadedColliders[gameObject->collider_index]) {
//             std::cerr << "Error: Collider index not found or is null for player!" << std::endl;
//             return {};
//         }

//         std::shared_ptr<btCollisionObject> gameObjectCollisionObject = std::make_shared<btCollisionObject>();        ;
//         gameObjectCollisionObject->setCollisionShape(loadedColliders[gameObject->collider_index].get());

//         if (CheckCollision(player_collision_object, gameObjectCollisionObject)) {
//             result.push_back(gameObject);
//         }
//     }
//     return result;
// }

// std::vector<std::shared_ptr<GameObject>> BulletPhysics::Raycast(std::shared_ptr<GameObject> self, btVector3 ray, float magnitude, btVector3 startPointOffset) {
    // std::vector<std::shared_ptr<GameObject>> hitObjects;
    // btVector3 rayStart = self->position + startPointOffset;
    // btVector3 rayEnd = rayStart + ray * magnitude;

    // btCollisionWorld::AllHitsRayResultCallback rayCallback(rayStart, rayEnd);

    // this->collisionWorld->rayTest(rayStart, rayEnd, rayCallback);

    // if (rayCallback.hasHit()) {
    //     for (int i = 0; i < rayCallback.m_collisionObjects.size(); i++) {
    //         const btCollisionObject* hitObj = rayCallback.m_collisionObjects[i];
    //         GameObject* rawPointer = static_cast<GameObject*>(hitObj->getUserPointer());

    //         if (!rawPointer) {
    //             std::cout << "GameObject is nullptr at index: " << i << std::endl;
    //             continue;
    //         }
    //         std::shared_ptr<GameObject> gameObject = rawPointer->shared_from_this();
            
    //         if (gameObject && gameObject != self) {
    //             hitObjects.push_back(gameObject);
    //         }
    //     }
    // }

    // return hitObjects;
// }

// std::shared_ptr<GameObject> BulletPhysics::GetGameObjectFromId(int collider_id) {
//     return this->loadGameObjectsMapped[collider_id];
// }

// btCollisionWorld::ClosestConvexResultCallback BulletPhysics::CollideAndSlideCollisionCheck(std::shared_ptr<GameObject> self, btTransform startTransform, btTransform endTransform) {
//     std::shared_ptr<btConvexHullShape> shape = this->loadedColliders[self->collider_index];
    
//     btCollisionWorld::ClosestConvexResultCallback hitCallback(startTransform.getOrigin(), endTransform.getOrigin());

//     this->collisionWorld->convexSweepTest(shape.get(), startTransform, endTransform, hitCallback);

//     return hitCallback;
// }