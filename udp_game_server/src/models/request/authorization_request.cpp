#include "models/request/authorization_request.h"
#include "string_utils/string_utils.h"

AuthorizationRequest::AuthorizationRequest(std::string message) {
    this->userId = message.substr(0, 36);
    this->gameId = message.substr(36, 36);
}