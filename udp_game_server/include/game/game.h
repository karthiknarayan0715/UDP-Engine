#ifndef GAME_H
#define GAME_H

#include "engine/constants/includes.h"

#include "engine/game_object/game_object.h"
#include "game/physics_manager.h"
#include "game/map.h"

class Game {
    int gameTick;

    std::string game_id;
    std::vector<std::unique_ptr<GameObject>> players;
    
    public:
    Map* map;
    std::unique_ptr<PhysicsManager> physics;
    Game(std::string game_id);
    void AddPlayer(std::unique_ptr<GameObject> player);
    void Start();
    void Update();
    std::string GetGameId();
    std::vector<GameObject*> GetPlayers();
    void Broadcast(std::string message);
};

#endif