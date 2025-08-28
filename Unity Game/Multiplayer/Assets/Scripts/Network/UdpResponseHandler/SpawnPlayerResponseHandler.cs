using System;
using GameScripts;
using Models.GameData;
using Models.Message.Server;
using Models.Message.UDP.Response;
using Unity.VisualScripting;
using UnityEngine;

namespace Network.UdpResponseHandler
{
    public class SpawnPlayerResponseHandler : BaseUdpResponseHandler
    {
        public void execute(string udpResponse)
        {
            try
            {
                SpawnPlayerUdpResponse spawnPlayerUdpResponse = new SpawnPlayerUdpResponse(udpResponse);
                bool isLocalPlayer =
                    spawnPlayerUdpResponse.clientId.Equals(GameManager.Instance.getUserData().getUUID());
                Player player = new Player(spawnPlayerUdpResponse.clientId, "username", 0, isLocalPlayer,
                    spawnPlayerUdpResponse.SpawnPoint, new Vector3(0, 0, 0), new Vector3(0, 0, 0), new Vector3(0, 0, 0), 100);
                MainThreadDispatcher.Instance.EnqueueAction(() => GameManager.Instance.GetCurrentGame().AddPlayer(player));
                UdpNetworkManager.Instance.SpawnPlayer(player);
            }
            catch (Exception e)
            {
                Debug.LogError(e);
                throw new Exception(e.Message);
            }
        }
    }
}