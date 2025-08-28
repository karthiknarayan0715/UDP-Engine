#ifndef CONSTANTS_H
#define CONSTANTS_H

#define PORT 4999
#define BUFFER_SIZE 1024

#define REQUEST_TYPE_LENGTH 1
#define REQUEST_INPUT_LENGTH 4

#define TICK_RATE 30


// <PLAYER_ID>:<FIELD_1>|<FIELD2>|<VECTOR>1,2,3;<PLAYER_ID2>..
#define FIELD_SEPERATOR "|"
#define REQUEST_SEPERATOR ":"
#define ENTITY_SEPERATOR ";"
#define VECTOR_SEPERATOR ","

#define RANDOM_SPAWN false

#define MAX_HEALTH 100

#include <spdlog/spdlog.h>

#endif