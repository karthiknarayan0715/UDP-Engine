#ifndef GAME_LOOP_H
#define GAME_LOOP_H

#include <thread>
#include <chrono>
#include <atomic>

class GameLoop{
    private:
        GameLoop(){}

    public:

    GameLoop(const GameLoop&) = delete;
    GameLoop& operator=(const GameLoop&) = delete;

    static GameLoop& GetInstance() {
        static GameLoop gameLoop;
        return gameLoop;
    }

    static void StartGameLoop();
};

#endif