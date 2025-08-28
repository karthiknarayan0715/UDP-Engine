#ifndef MESH_COLLIDER_H
#define MESH_COLLIDER_H

#include "engine/constants/includes.h"

class Mesh;

class MeshCollider : public Component{
    private:
    btTransform GetCurrentWorldTransform();
    btTransform GetCustomTransformFromVector3(Vector3 position);
    Vector3 offset;
    public:
    std::unique_ptr<btConvexHullShape> convexHullShape;
    std::unique_ptr<btCollisionObject> collisionObject;
    MeshCollider(Mesh* mesh);
    void Start();
    void Update();
    void UpdateTransform();
    void SetOffset(Vector3 offset);
    std::unique_ptr<Component> Clone() const override;
    btCollisionWorld::ClosestConvexResultCallback CheckAnyNewCollisions(Vector3 oldTransform, Vector3 newTransform);
};

#endif