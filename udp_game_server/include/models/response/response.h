#include "models/constants/constants.h"

class Response {
    char responseType;
    std::string message;

    public:
        Response(char responseType, std::string message);
        std::string GetResponse();
};