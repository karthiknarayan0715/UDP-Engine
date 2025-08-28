#ifndef PLAYER_MOVEMENT_H
#define PLAYER_MOVEMENT_H

#include "engine/constants/includes.h"

class Transform;
class PlayerInputs;

class PlayerMovement : public Component {
    Vector3 velocity;
    std::unique_ptr<Transform> newTransform;
    void ToggleIsJumping();
    bool IsGrounded();
    public:
    void Update() override;
    void CalculateVelocityVector(PlayerInputs* inputs, Transform* transform);
    void HandleGravity();
    void UpdateNewTransform(PlayerInputs* inputs, Transform* transform);
    void UpdatePlayerTransform(PlayerInputs* inputs, Transform* transform);
    void CollideAndSlide(PlayerInputs* inputs, Transform* transform);
};

#endif