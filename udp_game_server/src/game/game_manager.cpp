#include "engine/game_object/game_object.h"
#include "game/game_manager.h"
#include "game/player/player_info.h"

void GameManager::addGame(std::unique_ptr<Game> game) {
    this->games.push_back(std::move(game));
}

Game* GameManager::getGameByGameId(std::string gameId) {
    for (auto& game : games) {
        if (game->GetGameId() == gameId) {
            return game.get();
        }
    }
    return nullptr;
}

GameObject* GameManager::getPlayerByPlayerId(std::string playerId) {
    for (auto& game : games) {
        for (GameObject* player : game->GetPlayers()){
            if (player->GetComponent<PlayerInfo>()->clientId == playerId) {
                return player;
            }
        }
    }

    return nullptr;
}

void GameManager::Update() {
    for (std::unique_ptr<Game>& game : games) {
        game->Update();
    }
}