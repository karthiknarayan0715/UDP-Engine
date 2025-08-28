using System;
using System.Text.Json;

namespace Models.Message.Client
{
    public class ClientRequest : BaseRequest
    {
        private String endPoint;
        private String jsonMessage;
        
        public string EndPoint
        {
            get => endPoint;
            set => endPoint = value;
        }

        public string Message
        {
            get => jsonMessage;
            set => jsonMessage = value;
        }

        public ClientRequest(string endPoint, BaseRequest request)
        {
            this.endPoint = endPoint;
            this.jsonMessage = request.getMessage();
        }

        public string getMessage()
        {
            var jsonObject = new
            {
                endpoint = this.endPoint ?? "",
                message = this.jsonMessage ?? "{}"
            };

            // Serialize to JSON
            return JsonSerializer.Serialize(jsonObject);
        }

    }
}