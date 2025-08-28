#include <iostream>
#include <vector>
#include <memory>
#include <string.h>

class Player;
class Game;
class Vector3;

class GameDataResponse {
    Game* game;

    public:
    GameDataResponse(Game* game);
    std::string ToString();
};