#include "models/constants/constants.h"
#include <string>

class Request {
    public:
    char requestType;
    std::string message;

    Request(std::string buffer);
};