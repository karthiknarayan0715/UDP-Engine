using System.Text.Json;
using Static;

namespace Models.Message.Client
{
    public class FindMatchRequest : BaseRequest 
    {
        private string uuid;
        private GameMode gameMode;
        private string requestTime;

        public FindMatchRequest(string uuid, GameMode gameMode)
        {
            this.uuid = uuid;
            this.gameMode = gameMode;
        }
        
        public void setRequestTime(string requestTime) {
            this.requestTime = requestTime;
        }
        
        public string getMessage() {
            var jsonObject = new
            {
                uuid = this.uuid ?? "",
                gameMode = this.gameMode.ToString(),
                requestTime = this.requestTime ?? ""
            };
            return JsonSerializer.Serialize(jsonObject);
        }
    }
}