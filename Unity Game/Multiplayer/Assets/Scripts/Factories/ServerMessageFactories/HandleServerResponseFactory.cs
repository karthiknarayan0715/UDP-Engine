using Network;

namespace Factories.ServerMessageFactories
{
    public class HandleServerResponseFactory
    {

        public static HandleServerResponse create() {
            return new HandleServerResponse();
        }
    }
}