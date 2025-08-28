#include "game/player/player_health.h"
#include "game/player/player_info.h"

void PlayerHealth::Start() {
    this->health = 100;
}

float PlayerHealth::GetHealth() {
    return this->health;
}

void PlayerHealth::TakeDamage(float damage) {
    spdlog::debug("In ShootLoop2()");
    this->health -= damage;
    spdlog::debug("In ShootLoop3()");
    if (this->gameObject != nullptr && this->gameObject->GetComponent<PlayerInfo>() != nullptr){
        spdlog::debug("Player {} took a damage of {}, current health: {}", this->gameObject->GetComponent<PlayerInfo>()->clientId, damage, this->health);
    }
}