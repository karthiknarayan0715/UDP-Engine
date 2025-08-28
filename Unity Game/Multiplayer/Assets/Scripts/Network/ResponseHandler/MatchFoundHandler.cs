using System.Text.Json;
using Models.Message.Client;
using Models.Message.Server;
using Models.MetaData;
using UnityEngine;

namespace Network.ResponseHandler
{
    public class MatchFoundHandler : BaseResponseHandler
    {
        public void execute(ServerResponse serverResponse)
        {
            MatchFoundResponse matchFoundResponse = JsonSerializer.Deserialize<MatchFoundResponse>(serverResponse.getResponse());
            
            Debug.Log("MatchFoundResponse: " + serverResponse.getResponse() + ":" +matchFoundResponse + ":" + matchFoundResponse.getGameId());

            if (matchFoundResponse.getGameId() != null)
            {
                GameManager.Instance.SetGameData(new GameData(matchFoundResponse.getGameId()));
                // MainThreadDispatcher.Instance.EnqueueCoroutine(UdpNetworkManager.Instance.());
                UiManager.Instance.matchFound = true;
                MainThreadDispatcher.Instance.EnqueueAction(() => LevelManager.Instance.LoadGameScene());
            }
        }
    }
}