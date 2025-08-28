using System;
using System.Text.Json;

namespace Models.Message.Server
{
    public class ServerResponse : BaseResponse
    {
        public String Endpoint { get; set; }
        public String Response { get; set; }

        public String getResponse()
        {
            return Response;
        }

    }
}