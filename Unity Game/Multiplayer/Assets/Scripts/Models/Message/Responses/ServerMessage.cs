using System;
using Factories.ServerMessageFactories;
using Models.Message;
using Newtonsoft.Json;
using Newtonsoft.Json.Linq;
using UnityEngine;

namespace Models.Message.Server
{
    public class ServerMessage
    {
        private ServerHeadersInfo _serverHeadersInfo;
        private String _jsonData;
        
        public ServerMessage(ServerHeadersInfo serverHeadersInfo, string message) {
            this._serverHeadersInfo = serverHeadersInfo;
            this._jsonData = message;
        }

        public ServerMessage(string message)
        {
            this._serverHeadersInfo = getHeaders(message);
            this._jsonData = getJsonData(message);
        }

        private ServerHeadersInfo getHeaders(string serverMessage)
        {
            return ServerHeadersInfoFactory.create(int.Parse(serverMessage.Split("\t")[0].Split(" ")[1]), serverMessage.Split("\t")[1].Split(" ")[1]);
        }
        
        private string getJsonData(string message) {
            return message.Split("\n")[1];
        }

        public ServerResponse getServerResponse()
        {
            try
            {
                return JsonConvert.DeserializeObject<ServerResponse>(this._jsonData);
            }
            catch (Exception e)
            {
                Debug.LogError("Error reading data from server: " + e.Message);
                return null;
            }
        }
    }
}