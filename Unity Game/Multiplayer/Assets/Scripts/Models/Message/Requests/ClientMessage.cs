using System;
using Factories.ClientMessageFactories;

namespace Models.Message.Client
{
    public class ClientMessage
    {
        private ClientHeadersInfo _clientHeadersInfo;
        private String message;
        
        public ClientMessage(ClientHeadersInfo clientHeadersInfo, String message) {
            this._clientHeadersInfo = clientHeadersInfo;
            this.message = message;
        }

        public ClientMessage(String message) {
            this.message = message;
            this._clientHeadersInfo = getDefaultHeaders();
        }
        
        public String getMessage() {
            return _clientHeadersInfo.getHeaders() + message;
        }
        
        private ClientHeadersInfo getDefaultHeaders() {
            return ClientHeadersInfoFactory.create(Constants.DEFAULT_CONTENT_TYPE, message.Length);
        }

    }
}