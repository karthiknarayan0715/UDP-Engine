#include "models/constants/constants.h"
#include <string>

class AuthorizationRequest {
    public:
        std::string userId, gameId;
        AuthorizationRequest() {};
        AuthorizationRequest(std::string message);
};