#ifndef RANDOM_CUSTOM_H
#define RANDOM_CUSTOM_H

#include <iostream>
#include <random>
#include "utils/vector3/vector3.h"

int getRandomNumber(int min, int max) {
    std::random_device rd;  // Seed
    std::mt19937 gen(rd()); // Mersenne Twister RNG
    std::uniform_int_distribution<int> dist(min, max);
    return dist(gen);
}

Vector3 GetRandomVector(int min, int max) {
    return Vector3(getRandomNumber(min * 100, max * 100) / 100, getRandomNumber(min * 100, max * 100) / 100, getRandomNumber(min * 100, max * 100) / 100);
}

Vector3 GetRandomSpawnPoint(int min, int max) {
    return Vector3(getRandomNumber(min * 100, max * 100) / 100, 0, getRandomNumber(min * 100, max * 100) / 100);
}

Vector3 GetSpawnPoint() {
    return Vector3(0, 20, 0);
}


#endif