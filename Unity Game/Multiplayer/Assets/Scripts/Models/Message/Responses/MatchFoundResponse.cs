using System.Collections;
using System.Collections.Generic;
using System.Text.Json.Serialization;

namespace Models.Message.Server
{
    public class MatchFoundResponse : BaseResponse
    {
        [JsonInclude] private string gameId;
        [JsonInclude] List<PlayerInfo> players;
        
        public MatchFoundResponse(string gameId, List<PlayerInfo> players)
        {
            this.gameId = gameId;
            this.players = players;
        }
        
        public string getGameId() => gameId;
        public List<PlayerInfo> getPlayers() => players;
    }
}