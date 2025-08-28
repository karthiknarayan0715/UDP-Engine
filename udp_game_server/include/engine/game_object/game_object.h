#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "engine/constants/includes.h"
#include <shared_mutex>

class Component;

class Game;

class GameObject {
    public:
    std::map<std::type_index, std::unique_ptr<Component>> components;
    std::string name;
    Game* game;
    std::shared_mutex mapMutex;
    
    GameObject(Vector3 position, Vector3 rotation, Vector3 scale = Vector3(1, 1, 1));
    
    template<typename T>
    T* AddComponent(std::unique_ptr<T> component) {
        std::lock_guard<std::shared_mutex> lock(mapMutex);
        component->gameObject = this;
        T* rawPtr = component.get();
        components[typeid(T)] = std::move(component);
        return rawPtr;
    }
    
    template<typename T>
    T* GetComponent() {
        std::lock_guard<std::shared_mutex> lock(mapMutex);
        auto it = components.find(typeid(T));
        if (it != components.end()) {
            return static_cast<T*>(it->second.get());
        }
        return nullptr;
    }

    std::unique_ptr<GameObject> Clone();

    // Delete copy constructor and copy assignment operator
    GameObject(const GameObject&) = delete;
    GameObject& operator=(const GameObject&) = delete;

    // Default move constructor and move assignment operator
    GameObject(GameObject&&) noexcept = default;
    GameObject& operator=(GameObject&&) noexcept = default;

    void Start();

    void Update();

    void SetGame(Game* game) {
        this->game = game;
    }
};

#endif