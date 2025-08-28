using System.Text.Json;

namespace Models.Message.Client
{
    public class ConnectRequest : BaseRequest
    {
        private string uuid;
        private string username;

        public ConnectRequest(string uuid, string username)
        {
            this.uuid = uuid;
            this.username = username;
        }

        public string getMessage()
        {
            var jsonObject = new
            {
                uuid = this.uuid ?? "",
                username = this.username ?? ""
            };

            return JsonSerializer.Serialize(jsonObject);
        }
    }
}