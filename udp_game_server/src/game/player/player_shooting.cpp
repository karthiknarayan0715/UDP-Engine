#include "game/player/player_shooting.h"
#include "game/player/player_physics.h"
#include "game/player/player_constants.h"
#include "game/player/player_inputs.h"
#include "game/player/player_camera.h"
#include "game/player/player_health.h"

#include "engine/components/default/transform.h"

void PlayerShooting::Update() {
    this->Shoot();
}

void PlayerShooting::Shoot() {

    PlayerInputs* playerInputs = this->gameObject->GetComponent<PlayerInputs>();
    PlayerCamera* playerCamera = this->gameObject->GetComponent<PlayerCamera>();
    Transform* transform = this->gameObject->GetComponent<Transform>();
    PlayerPhysics* playerPhysics = this->gameObject->GetComponent<PlayerPhysics>();

    if (playerInputs == nullptr || playerCamera == nullptr || transform == nullptr || playerPhysics == nullptr) {
        spdlog::trace("Player Components are null");
        return;
    }

    if (!playerInputs->isShooting) {
        return;
    }

    float cameraPitch = playerCamera->rotation.x * M_PI / 180;
    float playerYaw = transform->rotation.y * M_PI / 180;

    Vector3 shoot_direction;
    shoot_direction.x = cos(cameraPitch) * sin(playerYaw);
    shoot_direction.y = -sin(cameraPitch); // For some reason unity apparently uses negative pitch while looking up, thats why the -ve sign
    shoot_direction.z = cos(cameraPitch) * cos(playerYaw);
    
    shoot_direction.normalize();

    Vector3 shootCameraOrigin = transform->position + this->gameObject->GetComponent<PlayerConstants>()->firstPersonCameraOffset;

    spdlog::debug("Position: {}, shootDir: {}", shootCameraOrigin.ToString(), shoot_direction.ToString());

    std::vector<GameObject*> hitObjects = playerPhysics->Raycast(shootCameraOrigin, shoot_direction, 1000);
    
    for (GameObject* object : hitObjects) {
        if (object == nullptr){
            spdlog::error("object is nullptr");
            continue;
        } 
        spdlog::debug("Hit player: {}", object->name);
        PlayerHealth* health = object->GetComponent<PlayerHealth>();
        if (health != nullptr) {
            health->TakeDamage(20);
        }
    }

    if (this->gameObject->GetComponent<PlayerInputs>() && this->gameObject->GetComponent<PlayerInputs>()->isShooting == true) {
        this->gameObject->GetComponent<PlayerInputs>()->isShooting = false;
    }
}