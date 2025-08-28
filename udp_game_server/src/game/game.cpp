#include "game/game.h"
#include "engine/game_object/game_object.h"
#include "game/physics_manager.h"
#include "game/map.h"
#include "game/player/player_info.h"
#include "models/constants/response_type_map.h"
#include "models/response/gamedata_response.h"
#include "models/response/response.h"

#include "server/server.h"

Game::Game(std::string game_id) {
    this->gameTick = 0;
    this->game_id = game_id;
    this->physics = std::make_unique<PhysicsManager>(game_id);
    this->physics->game = this;
    this->physics->LoadMap("map_collider");
}

void Game::AddPlayer(std::unique_ptr<GameObject> player){
    this->players.push_back(std::move(player));
}

void Game::Start() {
    for(std::unique_ptr<GameObject>& player : this->players) {
        player->Start();
    }
    this->map = this->physics->map.get();
    for(std::unique_ptr<GameObject>& mapObject : this->map->gameObjects) {
        mapObject->Start();
    }
}

void Game::Update() {
    for(std::unique_ptr<GameObject>& player : this->players) {
        player->Update();
    }
    GameDataResponse gameDataResponse = GameDataResponse(this);
    Response response = Response(ResponseType_GAMEDATA, gameDataResponse.ToString());
    Broadcast(response.GetResponse());
    this->gameTick++;
}

std::string Game::GetGameId() {
    return this->game_id;
}

std::vector<GameObject*> Game::GetPlayers() {
    std::vector<GameObject*> players;
    for (std::unique_ptr<GameObject>& player : this->players) {
        if (player != nullptr && player.get() != nullptr){
            players.push_back(player.get());
        }
    }
    return players;
}

void Game::Broadcast(std::string message) {
    for (const std::unique_ptr<GameObject>& player : this->players) {
        Server::getInstance().SendMessage(player->GetComponent<PlayerInfo>()->getClientSocket(), message);
    }
}