using Models.Message.Server;

namespace Factories.ServerMessageFactories
{
    public class ServerHeadersInfoFactory
    {
        public static ServerHeadersInfo create(int contentLength, string contentType) {
            return new ServerHeadersInfo(contentLength, contentType);
        }
    }
}