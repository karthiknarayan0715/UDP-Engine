using System;
using System.Net.Sockets;
using System.Text;
using System.Threading;
using Factories.ClientMessageFactories;
using Factories.ServerMessageFactories;
using Models.Message.Client;
using Models.Message.Server;
using UnityEngine;

namespace Network
{
    public class TcpConnector
    {
        private TcpClient _tcpClient;
        
        private NetworkStream _networkStream;

        private Thread _receiveThread;

        private bool _isConnected = false;

        public TcpConnector(String host, int port)
        {
            _tcpClient = new TcpClient(host, port);
            _networkStream = _tcpClient.GetStream();
            _isConnected = true;
            
            _receiveThread = new Thread(HandleReceivedMessage);
            _receiveThread.Start();
        }

        private void HandleReceivedMessage()
        {
            try
            {
                byte[] buffer = new byte[1024];

                while (_isConnected)
                {
                    int bytesRead = 0;

                    while ((bytesRead = _networkStream.Read(buffer, 0, buffer.Length)) != 0)
                    {
                        try
                        {
                            HandleServerResponse _handleServerResponse = HandleServerResponseFactory.create();
                            string serverMessageInput = Encoding.UTF8.GetString(buffer, 0, bytesRead);
                            Debug.Log("Server Replied: " + serverMessageInput);
                            ServerMessage serverMessage = ServerMessageFactory.create(serverMessageInput);
                            _handleServerResponse.execute(serverMessage.getServerResponse());
                        }
                        catch (Exception e)
                        {
                            Debug.LogError("Error Reading data from server: "+ e.ToString());
                        }
                    }
                }
            }
            catch (Exception e)
            {
                Debug.LogError("Error receiving data from server: " + e.Message);
            }
        }

        public void SendMessage(ClientRequest clientRequest)
        {
            if (!_isConnected) return;

            ClientMessage clientMessage = ClientMessageFactory.create(clientRequest.getMessage());
            byte[] dataToSend = Encoding.UTF8.GetBytes(clientMessage.getMessage());
            _networkStream.Write(dataToSend, 0, dataToSend.Length);
            _networkStream.Flush();
            Debug.Log("Sent to server: " + clientMessage.getMessage());
        }

        public void disconnect()
        {
            _isConnected = false;

            _networkStream?.Close();
            _tcpClient?.Close();

            if (_receiveThread != null && _receiveThread.IsAlive)
            {
                _receiveThread.Join();
            }
        }
    }
}