using Models.Message.Server;

namespace Factories.ServerMessageFactories
{
    public class ServerMessageFactory
    {
        public static ServerMessage create(string message)
        {
            return new ServerMessage(message);
        }
    }
}