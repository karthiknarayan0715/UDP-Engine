using Models.Message.Client;

namespace Factories.ClientMessageFactories
{
    public class ClientMessageFactory
    {
        public static ClientMessage create(string message)
        {
            return new ClientMessage(message);
        }
    }
}