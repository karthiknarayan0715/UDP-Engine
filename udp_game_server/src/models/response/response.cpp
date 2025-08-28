#include <string.h>
#include <string>
#include <sstream>
#include "models/response/response.h"

Response::Response(char responseType, std::string message) {
    this->message = message;
    this->responseType = responseType;
}

std::string Response::GetResponse() {
    std::ostringstream responseString;

    responseString << this->responseType << this->message;

    return responseString.str();
}