#ifndef INPUT_REQUEST_H
#define INPUT_REQUEST_H

#include <string>
#include <memory>

#include "models/constants/constants.h"
#include "models/game/inputs/player_inputs_request.h"

class PlayerInputsRequest;

class InputRequest {
    public:
    std::string player_id;
    PlayerInputsRequest player_inputs;
    InputRequest(){}
    InputRequest(std::string request);
};

#endif