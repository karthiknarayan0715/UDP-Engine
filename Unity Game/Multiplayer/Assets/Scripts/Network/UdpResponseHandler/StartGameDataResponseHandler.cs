using Models.Message.UDP.Response;
using UnityEngine;

namespace Network.UdpResponseHandler
{
    public class StartGameDataResponseHandler : BaseUdpResponseHandler
    {
        public void execute(string response)
        {
            Debug.Log("START Game Data Response: " + response);
            StartGameDataResponse startGameDataResponse = new StartGameDataResponse(response);
            startGameDataResponse.execute();
        }
    }
}