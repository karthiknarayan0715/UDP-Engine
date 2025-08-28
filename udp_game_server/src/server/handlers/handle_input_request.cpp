#include "server/handlers/handle_input_request.h"
#include "models/request/input_request.h"
#include "game/game_manager.h"
#include "models/game/inputs/player_inputs_request.h"
#include "game/player/player_inputs.h"
#include "engine/game_object/game_object.h"


void HandleInputRequest(InputRequest request) {
    GameObject* player = GameManager::GetInstance().getPlayerByPlayerId(request.player_id);
    
    if (player == nullptr) {
        spdlog::error("Player not added to GameManager");
        return;
    }

    PlayerInputsRequest player_input_request = request.player_inputs;
    if (player->GetComponent<PlayerInputs>() == nullptr) {
        player->AddComponent(std::make_unique<PlayerInputs>(player_input_request));
    }
    else {
        player->GetComponent<PlayerInputs>()->UpdateInputs(player_input_request);
    }
}