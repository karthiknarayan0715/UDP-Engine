#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H
#include "engine/constants/includes.h"
#include "game/game.h"

class GameManager {
    std::vector<std::unique_ptr<Game>> games;
    GameManager() {}
    
    public:
    void Update();
    GameManager(const GameManager&) = delete;
    GameManager& operator=(const GameManager&) = delete;

    static GameManager& GetInstance() {
        static GameManager Instance;
        return Instance;
    }

    void addGame(std::unique_ptr<Game> game);

    Game* getGameByGameId(std::string gameId);
    
    GameObject* getPlayerByPlayerId(std::string playerId);
};

#endif