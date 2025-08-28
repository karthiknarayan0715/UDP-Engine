using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using UnityEngine;
using System.Net;
using System.Net.Sockets;
using System.Text;
using GameScripts;
using Models.GameData;
using Models.Message.UDP;
using Models.Message.UDP.Constants;
using Models.Message.UDP.Request;
using Network;

public class UdpNetworkManager : MonoBehaviour
{
    [SerializeField]
    private string serverHost = "127.0.0.1";
    
    [SerializeField] private int serverPort = 4999;

    [SerializeField] public bool testing = false;
    
    [SerializeField] private GameObject localPlayerPrefab;
    
    [SerializeField] private GameObject remotePlayerPrefab;

    public static UdpNetworkManager Instance;
    
    UdpConnector _udpConnector;
    
    private bool connected = false;

    private IEnumerator Start()
    {
        while (
            (MainThreadDispatcher.Instance == null || MainThreadDispatcher.Instance.IsInstantiated == false) ||
            (GameManager.Instance == null || GameManager.Instance.IsInitialized == false)
               )
        {
            yield return null;
        }
        
        if (UdpNetworkManager.Instance != null)
        {
            Destroy(this.gameObject);
        }
        else
        {
            UdpNetworkManager.Instance = this;
            DontDestroyOnLoad(this);
        }

        _udpConnector = new UdpConnector(serverHost, serverPort);

        Authorize();
    }

    private void Authorize()
    {
        AuthorizationMessage message;
        
        Debug.Log(GameManager.Instance.getUserData().getUUID());
        
        message = new AuthorizationMessage(GameManager.Instance.getUserData().getUUID(), testing ? Guid.Empty.ToString() : GameManager.Instance.GetGameData().getGameId());

        UdpRequest request = new UdpRequest(UdpRequestType.AUTHORIZE, message);
        
        SendMessage(request.GetMessage());
    }

    public void SendMessage(string _data)
    {
        _udpConnector.SendMessage(Encoding.UTF8.GetBytes(_data));
    }

    public void SpawnPlayer(Player player)
    {
        MainThreadDispatcher.Instance.EnqueueAction(()=>{SpawnPlayerFromMainThread(player);});
    }

    private void SpawnPlayerFromMainThread(Player player)
    {
        Debug.Log("In SpawnPlayer, Spawning at: " + player.position.x + ", " + player.position.y + ", " + player.position.z);
        Vector3 spawnPoint = new Vector3(player.position.x, player.position.y, player.position.z);

        try
        {
            if (player.isLocalPlayer)
            {
                GameObject playerInstance = Instantiate(localPlayerPrefab, spawnPoint, Quaternion.identity);
                playerInstance.name = "local_" + player.clientId;
                playerInstance.GetComponent<PlayerMovement>()._player = player;
                player.SetPlayerGameObject(playerInstance);
                player.SetPlayerCameraGameObject(playerInstance.transform.Find("CameraHolder").gameObject);
            }
            else
            {
                GameObject playerInstance = Instantiate(remotePlayerPrefab, spawnPoint, Quaternion.identity);
                playerInstance.name = "remote_" + player.clientId;
                player.SetPlayerGameObject(playerInstance);
                player.SetPlayerCameraGameObject(playerInstance.transform.Find("GunModel").gameObject);
            }
        }
        catch (System.Exception ex)
        {
            Debug.LogError("Error spawning player: " + ex.Message);
        }
    }


}
