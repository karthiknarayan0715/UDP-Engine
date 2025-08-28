#include "models/request/request.h"
#include "string_utils/string_utils.h"

Request::Request(std::string buffer){
    requestType = buffer[0];
    this->message = buffer.substr(1);
}