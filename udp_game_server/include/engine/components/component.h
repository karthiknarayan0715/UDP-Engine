#ifndef COMPONENT_H
#define COMPONENT_H

#include "engine/constants/includes.h"

class GameObject;

class Component {
    public:
    GameObject* gameObject;
    virtual ~Component();
    virtual void Start() {}
    virtual void Update() {}
    virtual std::unique_ptr<Component> Clone() const {
        return nullptr;
    };
};

#endif