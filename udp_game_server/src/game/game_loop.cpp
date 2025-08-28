#include "game/game_loop.h"
#include "models/constants/constants.h"
#include "game/game_manager.h"

const double FRAME_TIME = 1000.0 / TICK_RATE;

void GameLoop::StartGameLoop() {
    try {
        spdlog::info("Started game loop thread with TICK_RATE: {}", TICK_RATE);
        int frames = 0;
        auto secondCounterRef = std::chrono::high_resolution_clock::now();
        while (true) {
            auto startTime = std::chrono::high_resolution_clock::now();
            frames++;

            double secondsElapsed = std::chrono::duration<double>(startTime - secondCounterRef).count();

            if (secondsElapsed >= 10) {
                spdlog::info("Average Frame rate: {}", frames / secondsElapsed);
                frames = 0;
                secondCounterRef = std::chrono::high_resolution_clock::now();
            }

            // Process player inputs
            // Update game logic and state
            // Broadcast updated game state to clients
            GameManager::GetInstance().Update();

            auto endTime = std::chrono::high_resolution_clock::now(); 
            double elapsedTime = std::chrono::duration<double, std::milli>(endTime - startTime).count();
            double waitTime = FRAME_TIME - elapsedTime;
            
            std::this_thread::sleep_for(std::chrono::duration<double, std::milli>(waitTime));
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error occurred: " << e.what() << std::endl;
    }  
}