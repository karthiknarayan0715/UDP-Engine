#include "game/game.h"
#include "game/player/player_info.h"
#include "engine/game_object/game_object.h"
#include "models/response/gamedata_response.h"
#include <sstream>

GameDataResponse::GameDataResponse(Game* game) {
    this->game = game;
}

std::string GameDataResponse::ToString() 
{
    std::ostringstream responseBuffer;
    if (this->game == nullptr) {
        spdlog::error("The game is null");
        return "";
    }
    if(this->game->GetPlayers().size() <= 0) {
        spdlog::debug("No players in the game yet!");
    }

    for (size_t i=0; i<this->game->GetPlayers().size(); ++i) {
        responseBuffer << (this->game->GetPlayers()[i]->GetComponent<PlayerInfo>()->ToString());
        if (i < this->game->GetPlayers().size() - 1) {
            responseBuffer << ";";
        }
    }

    return responseBuffer.str();
}