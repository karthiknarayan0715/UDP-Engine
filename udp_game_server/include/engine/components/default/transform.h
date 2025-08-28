#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "engine/constants/includes.h"


class Transform : public Component {
    public:
    Vector3 position, rotation, scale;
    Transform(Vector3 position, Vector3 rotation, Vector3 scale = Vector3(1, 1, 1));
    Transform(Transform* Transform);
    void UpdateTransform(Transform* Transform);
};

#endif