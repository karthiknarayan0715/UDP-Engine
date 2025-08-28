using System.Text.Json.Serialization;

namespace Models
{
    public class PlayerInfo
    {
        [JsonInclude] private string uuid;
        [JsonInclude] private string username;
        [JsonInclude] private int team;
        
        public PlayerInfo(string uuid, string username, int team)
        {
            this.uuid = uuid;
            this.username = username;
            this.team = team;
        }
        
        public string getUUID() => uuid;
        public string getUsername() => username;
        public int getTeam() => team;
        
    }
}