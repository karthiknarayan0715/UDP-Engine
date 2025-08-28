#include "game/player/player_movement.h"
#include "game/player/player_inputs.h"
#include "game/player/player_camera.h"
#include "game/player/player_info.h"
#include "game/player/player_physics.h"
#include "game/player/player_constants.h"
#include "game/game.h"

#include "engine/components/default/mesh.h"
#include "engine/components/default/mesh_collider.h"
#include "engine/game_object/game_object.h"
#include "engine/components/default/transform.h"

#include "models/constants/movement_constants.h"

void PlayerMovement::Update() {
    PlayerInputs* inputs = this->gameObject->GetComponent<PlayerInputs>();
    Transform* transform = this->gameObject->GetComponent<Transform>();
    if (transform == nullptr) {
        spdlog::error("PlayerTransform not found");
        return;
    }
    this->CalculateVelocityVector(inputs, transform);
}

void PlayerMovement::CalculateVelocityVector(PlayerInputs* inputs, Transform* transform)
{
    Vector3 movementVelocityVector = this->velocity;
    Vector3 gravityVelocityVector = Vector3(0, this->velocity.y, 0);

    Vector3 forwardVector = Vector3::GetPlayerForwardVector(transform->rotation);
    Vector3 rightVector = forwardVector.getRightVector();

    // Get mouse inputs, and validate it
    if (inputs != nullptr) {
        movementVelocityVector = forwardVector * inputs->moveZ + rightVector * inputs->moveX;
    }

    if (inputs != nullptr && (inputs->moveX != 0 || inputs->moveZ != 0)) {
        spdlog::trace("Move X: {} | Move Z: {}", inputs->moveX, inputs->moveZ);
    }

    if (inputs != nullptr && inputs->isJumping) {
        spdlog::debug("Jumping, IsGrounded: {}", this->IsGrounded());
    }
    
    if (movementVelocityVector.getMagnitude() != 0)
    {
        movementVelocityVector = movementVelocityVector.normalized();
    }
    
    this->velocity.x = movementVelocityVector.x;
    this->velocity.y = (inputs != nullptr && inputs->isJumping == true && this->IsGrounded()) ? JUMP_VELOCITY : gravityVelocityVector.y;
    this->velocity.z = movementVelocityVector.z;
    
    this->HandleGravity();


    if (inputs != nullptr && inputs->isJumping) {
        inputs->isJumping = false;
    }

    this->UpdateNewTransform(inputs, transform);
}

void PlayerMovement::HandleGravity() {
    this->velocity.y -= GRAVITY * (1.0f / TICK_RATE);
    if (this->velocity.y < -MAX_FALLING_SPEED) {
        this->velocity.y = -MAX_FALLING_SPEED;
    }
}

void PlayerMovement::UpdateNewTransform(PlayerInputs* inputs, Transform* transform)
{
    float speedPerTick = MOVEMENT_SPEED * (1.0f / TICK_RATE);
    
    // FORMAT: x * MovementSpeed, y * gravity, z * movementSpeed
    Vector3 newPosition;
    
    Vector3 movementVector;

    movementVector.x = this->velocity.x * speedPerTick;
    movementVector.y = this->velocity.y * (1.0f / TICK_RATE);
    movementVector.z = this->velocity.z * speedPerTick;

    this->newTransform = std::make_unique<Transform>(transform);

    newPosition = this->newTransform->position + movementVector;
    this->newTransform->position = newPosition;

    this->CollideAndSlide(inputs, transform);
}

void PlayerMovement::CollideAndSlide(PlayerInputs* inputs, Transform* transform) {
    int MAX_DEPTH = 5;
    
    for (int iteration = 0; iteration < MAX_DEPTH; iteration++) {
        if (this->gameObject->GetComponent<MeshCollider>() == nullptr) {
            spdlog::error("No mesh collider for the GO");
        }
        Vector3 movementVector = this->newTransform->position - transform->position;

        std::string client_id = this->gameObject->GetComponent<PlayerInfo>()->clientId;

        btCollisionWorld::ClosestConvexResultCallback hitResult = this->gameObject->GetComponent<MeshCollider>()->CheckAnyNewCollisions(transform->position, newTransform->position);
        if (hitResult.hasHit()) {
            Vector3 hitNormal = Vector3::getVector3FromBtVector3(hitResult.m_hitNormalWorld);
            Vector3 slidedPosition = movementVector - (hitNormal * Vector3::dot(movementVector, hitNormal));
            this->newTransform->position = transform->position + slidedPosition;
        }
        else {
            break;
        }
    }
    
    this->UpdatePlayerTransform(inputs, transform);
}

void PlayerMovement::UpdatePlayerTransform(PlayerInputs* inputs, Transform* transform) {
    transform->position = this->newTransform->position;

    if (inputs != nullptr) {
        this->newTransform->rotation = inputs->playerRotation;
        transform->rotation = inputs->playerRotation;
        if (this->gameObject->GetComponent<PlayerCamera>() != nullptr) {
            this->gameObject->GetComponent<PlayerCamera>()->rotation = inputs->cameraRotation;
        }
        else {
            spdlog::error("Player camera not loaded yet");
        }
    }
    if (this->gameObject->GetComponent<MeshCollider>() != nullptr) {
        this->gameObject->GetComponent<MeshCollider>()->UpdateTransform();
    }
    else {
        spdlog::error("Mesh collider not loaded yet");
    }
}

bool PlayerMovement::IsGrounded() {
    std::vector<GameObject*> groundCollisionGOs = this->gameObject->GetComponent<PlayerPhysics>()->Raycast(this->newTransform->position, -Vector3::WORLD_UP + this->gameObject->GetComponent<PlayerConstants>()->groundCheckOffset, this->gameObject->GetComponent<PlayerConstants>()->groundCheckDistance);
    if (groundCollisionGOs.size() > 0) {
        ToggleIsJumping();
        return true;
    }
    return false;
}

void PlayerMovement::ToggleIsJumping() {
    if (this->gameObject->GetComponent<PlayerInputs>()->isJumping == false) {
        this->gameObject->GetComponent<PlayerInputs>()->isJumping = true;
    }
}