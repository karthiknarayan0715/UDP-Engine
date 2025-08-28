
#include "server/handlers/handle_authorization_request.h"
#include "server/server.h"

#include "models/constants/request_type_map.h"
#include "models/constants/response_type_map.h"

#include "models/request/authorization_request.h"

#include "models/response/response.h"
#include "models/response/spawnplayer_response.h"
#include "models/response/gamedata_response.h"

#include "game/game.h"
#include "game/game_manager.h"
#include "game/player/player_info.h"
#include "game/player/player_camera.h"
#include "game/player/player_movement.h"
#include "game/player/player_constants.h"
#include "game/player/player_physics.h"
#include "game/player/player_shooting.h"
#include "game/player/player_health.h"

#include "engine/game_object/game_object.h"
#include "engine/components/default/mesh.h"
#include "engine/components/default/mesh_collider.h"
#include "engine/components/default/transform.h"

#include "utils/random_custom.h"

void HandleAuthorizationRequest(sockaddr_in clientSocket, AuthorizationRequest request) {
    spdlog::debug("gameId: {}, clientId: {}", request.gameId, request.userId);

    //Check if game exists, if not create the game
    Game* current_game = GameManager::GetInstance().getGameByGameId(request.gameId);
    if(current_game == nullptr) {
        spdlog::debug("No game found, creating the game");
        std::unique_ptr<Game> new_game = std::make_unique<Game>(request.gameId);
        current_game = new_game.get();
        GameManager::GetInstance().addGame(std::move(new_game));
        current_game->Start();
    }

    spdlog::info("current_game location id: {}", static_cast<const void*>(current_game));

    GameDataResponse gameData = GameDataResponse(current_game);
    std::string gameDataResponseString = gameData.ToString();

    Response gameDataResponse = Response(ResponseType_START_GAMEDATA, gameDataResponseString);
    std::string responseMessage = gameDataResponse.GetResponse();
    Server::getInstance().SendMessage(clientSocket, responseMessage);

    Vector3 spawn_point;
    if (RANDOM_SPAWN) {
        spawn_point = GetRandomSpawnPoint(0, 100);
    }
    else {
        spawn_point = GetSpawnPoint();
    }

    CreatePlayer(spawn_point, clientSocket, request, current_game);

    SpawnPlayerResponse spawnPlayerResponse = SpawnPlayerResponse(spawn_point, request.userId);

    std::string spawnPlayerResponseString = spawnPlayerResponse.GetMessage();

    Response response = Response(ResponseType_SPAWNPLAYER, spawnPlayerResponseString);

    std::string responseString = response.GetResponse();

    current_game->Broadcast(responseString);
}

void CreatePlayer(Vector3 &spawn_point, sockaddr_in &clientSocket, AuthorizationRequest &request, Game *current_game)
{
    Vector3 speed = Vector3();
    Vector3 playerRotation = Vector3();
    Vector3 cameraRotation = Vector3();

    std::unique_ptr<GameObject> player = std::make_unique<GameObject>(spawn_point, playerRotation);

    player->AddComponent<PlayerInfo>(std::make_unique<PlayerInfo>(clientSocket, request.userId, speed));
    player->AddComponent<PlayerCamera>(std::make_unique<PlayerCamera>(cameraRotation));
    player->AddComponent<PlayerMovement>(std::make_unique<PlayerMovement>());
    player->AddComponent<Mesh>(std::make_unique<Mesh>());

    player->GetComponent<Mesh>()->LoadPlayer();

    player->AddComponent<MeshCollider>(std::make_unique<MeshCollider>(player->GetComponent<Mesh>()));
    player->AddComponent<PlayerPhysics>(std::make_unique<PlayerPhysics>());
    player->AddComponent<PlayerConstants>(std::make_unique<PlayerConstants>());

    player->AddComponent<PlayerHealth>(std::make_unique<PlayerHealth>());
    player->AddComponent<PlayerShooting>(std::make_unique<PlayerShooting>());

    player->game = current_game;

    player->Start();

    current_game->AddPlayer(std::move(player));
}