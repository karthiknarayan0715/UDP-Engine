#include <vector>

#include "models/request/input_request.h"
#include "string_utils/string_utils.h"
#include "models/game/inputs/player_inputs_request.h"

InputRequest::InputRequest(std::string request) {
    std::vector<std::string> request_split = split(request, REQUEST_SEPERATOR);
    this->player_id = request_split[0];
    this->player_inputs = PlayerInputsRequest(request_split[1]);
};