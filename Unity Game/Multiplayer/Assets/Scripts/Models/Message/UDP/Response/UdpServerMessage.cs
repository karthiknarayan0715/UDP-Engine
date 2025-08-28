namespace Models.Message.UDP.Response
{
    public class UdpServerMessage
    {
        private char messageType;
        private string response;
        
        public char getMessageType() => messageType;
        public string getResponse() => response;

        public UdpServerMessage(string message)
        {
            messageType = message.Substring(0, 1).ToCharArray()[0];
            response = message.Substring(1);
        }
    }
}