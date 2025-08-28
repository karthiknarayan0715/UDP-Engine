using System.Text.Json;

namespace Models.Message.Server
{
    public class ConnectionResponse : BaseResponse
    {
        private string uuid;
        private string username;

        public ConnectionResponse(string uuid, string username)
        {
            this.uuid = uuid;
            this.username = username;
        }

        public string getResponse()
        {
            throw new System.NotImplementedException();
        }
    }
}