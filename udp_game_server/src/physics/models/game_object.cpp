// #include "physics/models/game_object.h"
// #include "models/game/player.h"
// #include "physics/bullet/bullet_init.h"

// GameObject::GameObject(std::string filename) {
//     if (LoadGameObjectFromJson(filename)) {
//         std::cout<<"Loaded "<<filename<<" successfully!";
//     }
// }

// GameObject::GameObject(MeshObject meshObject) {
//     this->name = meshObject.name;
//     this->position = Vector3::getBtVector3(meshObject.position);
//     this->rotation = Vector3::getBtVector3(meshObject.rotation);
//     this->scale = Vector3::getBtVector3(meshObject.scale);
//     this->collider = MeshCollider(meshObject.vertices, meshObject.indices);
// }

// bool GameObject::LoadGameObjectFromJson(std::string filename) {
//     std::ifstream file(filename);
//     if (!file.is_open()) {
//         std::cerr << "Failed to open " << filename << std::endl;
//         return false;
//     }

//     json jsonData;
//     file >> jsonData;
//     file.close();

//     for (const auto& obj : jsonData["objects"]) {
//         this->name = obj["name"];
//         this->position = {obj["position"]["x"], obj["position"]["y"], obj["position"]["z"]};
//         this->rotation = {obj["rotation"]["x"], obj["rotation"]["y"], obj["rotation"]["z"]};
//         this->scale = {obj["scale"]["x"], obj["scale"]["y"], obj["scale"]["z"]};

//         for (const auto& vert : obj["meshVertices"]) {
//             btVector3 adjustedVertex = btVector3(
//                 vert["x"].get<float>(),
//                 vert["y"].get<float>(),
//                 vert["z"].get<float>()
//             );
//             this->collider.vertices.push_back(adjustedVertex);
//         }        

//         for (const auto& idx : obj["meshTriangles"]) {
//             this->collider.indices.push_back(idx);
//         }
//     }
//     return true;
// }

// void GameObject::LoadTransform(std::shared_ptr<PlayerTransform> transform) {
//     this->position = Vector3::getBtVector3(transform->position);
//     this->rotation = Vector3::getBtVector3(transform->playerRotation);
// }

// bool GameObject::IsCollidingWithAnything(std::shared_ptr<PlayerTransform> transform){
//     LoadTransform(transform);
//     std::vector<std::shared_ptr<GameObject>> collidingObjects = BulletPhysics::GetInstance().GetCollisions(shared_from_this());
//     return collidingObjects.size() > 0;
// }

// bool GameObject::IsGrounded(std::shared_ptr<Player> player){
//     LoadTransform(player->getTransform());
//     btVector3 WORLD_DOWN = btVector3(0, -1, 0);
//     std::vector<std::shared_ptr<GameObject>> collidingObjects = BulletPhysics::GetInstance().Raycast(shared_from_this(), WORLD_DOWN, 0.4, Vector3::getBtVector3(player->GetGroundCheckRaycastOffset()));
//     return collidingObjects.size() > 0;
// }