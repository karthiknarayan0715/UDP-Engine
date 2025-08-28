#include <iostream>
#include "server/handle_request.h"
#include "server/handlers/handle_authorization_request.h"
#include "server/handlers/handle_input_request.h"

#include "models/request/request.h"
#include "models/constants/request_type_map.h"
#include "models/request/authorization_request.h"
#include "models/request/input_request.h"


void HandleRequest(sockaddr_in clientSocket ,Request request) {
    AuthorizationRequest authRequest;
    InputRequest inputRequest;

    switch (request.requestType)
    {
    case RequestType_AUTHORIZATION:
        authRequest = AuthorizationRequest(request.message);
        HandleAuthorizationRequest(clientSocket, authRequest);
        break;

    case RequestType_INPUT:
        inputRequest = InputRequest(request.message);
        HandleInputRequest(inputRequest);
        break;
    
    default:
        spdlog::error("Invalid request: {}, RID: ", request.message, (int)request.requestType);
        break;
    }
}