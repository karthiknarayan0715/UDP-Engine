using Models.Message.UDP.Response;
using UnityEngine;

namespace Network.UdpResponseHandler
{
    public class GameDataResponseHandler : BaseUdpResponseHandler
    {
        public void execute(string response)
        {
            GameDataResponse gameDataResponse = new GameDataResponse(response);
            gameDataResponse.execute();
        }
    }
}