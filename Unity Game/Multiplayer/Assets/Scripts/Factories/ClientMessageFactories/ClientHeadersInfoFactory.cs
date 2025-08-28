using Models.Message.Client;

namespace Factories.ClientMessageFactories
{
    public class ClientHeadersInfoFactory
    {
        public static ClientHeadersInfo create(string contentType, int contentLength) {
            return new ClientHeadersInfo(contentType, contentLength);
        }
    }
}