#include "game/player/player_constants.h"
#include "engine/components/default/mesh_collider.h"

void PlayerConstants::Start() {
    this->gameObject->GetComponent<MeshCollider>()->SetOffset(this->playerBodyGroundOffset);
}