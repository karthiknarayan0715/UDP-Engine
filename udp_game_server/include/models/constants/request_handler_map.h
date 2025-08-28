#include <iostream>
#include <map>
#include "models/constants/request_type_map.h"

static std::map<RequestType, void(*)()> RequestHandlerMap = std::map<RequestType, void(*)()> {

};