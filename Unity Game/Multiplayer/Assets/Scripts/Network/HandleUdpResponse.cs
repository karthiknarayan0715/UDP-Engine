using System;
using System.Collections.Generic;
using Models.Message.Server;
using Models.Message.UDP.Constants;
using Models.Message.UDP.Request;
using Models.Message.UDP.Response;
using Network.ResponseHandler;
using Network.UdpResponseHandler;
using Static;
using UnityEngine;

namespace Network
{
    public class HandleUdpResponse
    {
        private Dictionary<int, BaseUdpResponseHandler> responseHandlers = new Dictionary<int, BaseUdpResponseHandler>
        {
            {(int)UdpResponseType.SPAWNPOINT, new SpawnPlayerResponseHandler()},
            {(int)UdpResponseType.START_GAMEDATA, new StartGameDataResponseHandler()},
            {(int)UdpResponseType.GAMEDATA, new GameDataResponseHandler()}
        };
        
        public void execute(UdpServerMessage udpServerMessage)
        {
            try
            {
                // Debug.Log("GameData: " + (int)UdpResponseType.START_GAMEDATA);
                // Debug.Log("In HandleUdpResponse: " + (int)udpServerMessage.getMessageType());
                responseHandlers[udpServerMessage.getMessageType()].execute(udpServerMessage.getResponse());
            }
            catch (Exception e)
            {
                Debug.LogError(e.Message + "\n" + e.StackTrace);
            }
        }
    }
}