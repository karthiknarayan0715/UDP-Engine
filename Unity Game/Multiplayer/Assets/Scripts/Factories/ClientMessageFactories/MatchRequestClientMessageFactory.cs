using Models.Message.Client;
using Static;

namespace Factories.ClientMessageFactories
{
    public class MatchRequestClientMessageFactory
    {
        public static FindMatchRequest create(string uuid, GameMode gameMode)
        {
            return new FindMatchRequest(uuid, gameMode);
        }
    }
}