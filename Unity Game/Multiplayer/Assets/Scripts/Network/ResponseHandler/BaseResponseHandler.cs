using Models.Message.Client;
using Models.Message.Server;

namespace Network.ResponseHandler
{
    public interface BaseResponseHandler
    {
        public void execute(ServerResponse serverResponse);
    }
}