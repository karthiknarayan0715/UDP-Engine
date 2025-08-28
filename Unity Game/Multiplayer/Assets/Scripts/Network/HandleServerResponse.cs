using System.Collections.Generic;
using Models.Message.Server;
using Network.ResponseHandler;
using Static;
using UnityEngine;

namespace Network
{
    public class HandleServerResponse
    {
        private Dictionary<string, BaseResponseHandler> responseHandlers = new Dictionary<string, BaseResponseHandler>
        {
            {ResponseType.CONNECT, new ConnectionResponseHandler()},
            {ResponseType.MATCH_FOUND, new MatchFoundHandler()}
        };
        
        public void execute(ServerResponse serverResponse)
        {
            responseHandlers[serverResponse.Endpoint].execute(serverResponse);
        }
    }
}