using Models.Message.Client;

namespace Factories.ClientMessageFactories
{
    public class ClientRequestFactory
    {
        public static ClientRequest create(string endPoint, BaseRequest request)
        {
            return new ClientRequest(endPoint, request);
        }
    }
}