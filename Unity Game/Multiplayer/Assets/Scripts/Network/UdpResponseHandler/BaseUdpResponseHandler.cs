using Models.Message.UDP.Response;

namespace Network.UdpResponseHandler
{
    public interface BaseUdpResponseHandler
    {
        public void execute(string udpResponseString);
    }
}