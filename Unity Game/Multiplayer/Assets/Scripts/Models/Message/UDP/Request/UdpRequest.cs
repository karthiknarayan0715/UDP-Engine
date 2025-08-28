using System.Linq;
using Models.Message.UDP.Constants;

namespace Models.Message.UDP.Request
{
    public class UdpRequest
    {
        public UdpRequestType UdpRequestType;
        public UdpMessage message;
        
        public UdpRequest(UdpRequestType udpRequestType, UdpMessage message) {
            this.UdpRequestType = udpRequestType;
            this.message = message;
        }

        public string GetMessage()
        {
            return (char)UdpRequestType + message.getMessage();
        }
    }
}