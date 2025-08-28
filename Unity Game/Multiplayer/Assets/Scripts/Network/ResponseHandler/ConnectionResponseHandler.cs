using System;
using Models.Message;
using Models.Message.Client;
using Models.Message.Server;
using Static;
using UnityEngine;

namespace Network.ResponseHandler
{
    public class ConnectionResponseHandler : BaseResponseHandler
    {
        public void execute(ServerResponse serverResponse)
        {
            GameManager.Instance.changeGameState(GameState.LOBBY);
            Debug.Log("CONNECTED TO SERVER");
        }
    }
}