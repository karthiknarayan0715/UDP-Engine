using System;
using Network;

namespace Factories
{
    public class TcpConnectorFactory
    {
        public static TcpConnector create(string host, int port)
        {
            return new TcpConnector(host, port);
        }
    }
}