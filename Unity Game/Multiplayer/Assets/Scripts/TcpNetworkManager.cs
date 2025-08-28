using System;
using System.Collections;
using Factories;
using Factories.ClientMessageFactories;
using Models.Message.Client;
using Network;
using Static;
using TMPro;
using Unity.VisualScripting;
using UnityEngine;

public class TcpNetworkManager : MonoBehaviour
{
    [SerializeField]
    private string serverHost = "localhost";
    
    [SerializeField]
    private string serverPort = "4999";

    private TcpConnector _tcpConnector;
    
    public static TcpNetworkManager Instance;


    private IEnumerator Start()
    {
        if (TcpNetworkManager.Instance != null)
        {
            Destroy(TcpNetworkManager.Instance.GameObject());
        }

        TcpNetworkManager.Instance = this;
        DontDestroyOnLoad(this);
        
        while (GameManager.Instance == null || !GameManager.Instance.IsInitialized)
        {
            yield return null;
        }
        
        _tcpConnector = TcpConnectorFactory.create(serverHost, int.Parse(serverPort));
        
    }

    public void ConnectToServer(String usernameText)
    {
        GameManager.Instance.getUserData().setUsername(usernameText);
        ConnectRequest connectRequest = ConnectRequestFactory.create(GameManager.Instance.getUserData().getUUID(), usernameText);
        ClientRequest clientRequest = ClientRequestFactory.create("connect", connectRequest);
        _tcpConnector.SendMessage(clientRequest);
    }

    public void LookForMatch()
    {
        FindMatchRequest findMatchRequest = MatchRequestClientMessageFactory.create(GameManager.Instance.getUserData().getUUID(), GameMode.UNRATED);
        findMatchRequest.setRequestTime(DateTime.Now.ToString("O "));
        ClientRequest clientRequest = ClientRequestFactory.create("findMatch", findMatchRequest);
        _tcpConnector.SendMessage(clientRequest);
        UiManager.Instance.StartMatchSearch();
    }

    public void CancelMatchRequest()
    {
        UiManager.Instance.CancelMatchRequest();
    }

    private void OnApplicationQuit()
    {
        _tcpConnector.disconnect();
    }
}
