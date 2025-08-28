using Models.Message.Client;

namespace Factories.ClientMessageFactories
{
    public class ConnectRequestFactory
    {
        public static ConnectRequest create(string uuid, string username)
        {
            return new ConnectRequest(uuid, username);
        }
    }
}