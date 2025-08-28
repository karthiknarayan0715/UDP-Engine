#include "engine/components/default/transform.h"

Transform::Transform(Vector3 position, Vector3 rotation, Vector3 scale) {
    this->position = position;
    this->rotation = rotation;
    this->scale = scale;
}

Transform::Transform(Transform* transform) {
    this->UpdateTransform(transform);
}

void Transform::UpdateTransform(Transform* transform) {
    this->position = transform->position;
    this->rotation = transform->rotation;
    this->scale = transform->scale;
}