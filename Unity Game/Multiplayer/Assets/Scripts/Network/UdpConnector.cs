using System;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Text;
using Models.Message.UDP;
using Models.Message.UDP.Response;
using UnityEngine;

namespace Network
{
    public class UdpConnector
    {
        private string serverHost;

        private int serverPort;

        private IPEndPoint serverIp;
        
        private UdpClient UdpClient;
        
        
        public UdpConnector(string serverHost, int serverPort)
        {
            this.serverHost = serverHost;
            this.serverPort = serverPort;

            this.serverIp = new IPEndPoint(IPAddress.Parse(this.serverHost), serverPort);

            this.UdpClient = new UdpClient();

            UdpClient.BeginReceive(ReceiveMessages, serverIp);

        }

        public void SendMessage(byte[] _data)
        {
            byte[] message = _data;
            UdpClient.SendAsync(message, message.Length, serverIp);
        }

        public void ReceiveMessages(IAsyncResult _result)
        {
            HandleUdpResponse handleUdpResponse = new HandleUdpResponse();
            byte[] receivedBytes = UdpClient.EndReceive(_result, ref serverIp);
            UdpClient.BeginReceive(ReceiveMessages, serverIp);
            string message = Encoding.UTF8.GetString(receivedBytes);

            if (receivedBytes != null)
            {
                // Debug.Log("Received from server: " + Encoding.UTF8.GetString(receivedBytes));
                
                UdpServerMessage udpServerMessage = new UdpServerMessage(message);
            
                handleUdpResponse.execute(udpServerMessage);
            }
        }
    }
}