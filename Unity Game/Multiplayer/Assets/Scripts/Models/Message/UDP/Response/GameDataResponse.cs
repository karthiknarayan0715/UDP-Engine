using System;
using GameScripts;
using Models.GameData;
using UnityEngine;

namespace Models.Message.UDP.Response
{
    public class GameDataResponse
    {
        Game game;
        
        public GameDataResponse(string response)
        {
            game = GameManager.Instance.GetCurrentGame();
            UpdateGame(response);
        }
        void UpdateGame(string response)
        {
            try
            {
                if (response.Equals(String.Empty))
                {
                    return;
                }
                string[] playersString = response.Split(';');
                foreach (string playerString in playersString)
                {
                    string[] processString = playerString.Split(':');
                    string clientId = processString[0];
                    Player currentPlayer = game.GetPlayerById(clientId);
                    string[] processSubString = processString[1].Split('|');
                    if (currentPlayer == null) continue;
                    currentPlayer.position = Utils.Utils.getVector3FromString(processSubString[0]);
                    currentPlayer.speed = Utils.Utils.getVector3FromString(processSubString[1]);
                    currentPlayer.playerRotation = Utils.Utils.getVector3FromString(processSubString[2]);
                    currentPlayer.cameraRotation = Utils.Utils.getVector3FromString(processSubString[3]);
                    if (currentPlayer.isLocalPlayer && currentPlayer.health != float.Parse(processSubString[4]))
                    {
                        Debug.Log("Player took damage: " + (currentPlayer.health - float.Parse(processSubString[4])));
                    }
                    currentPlayer.health = float.Parse(processSubString[4]);
                }
            }
            catch (Exception e)
            {
                Debug.LogError("Message: " + e.Message + "\nStackTrace: " + e.StackTrace);
            }
            
        }

        public void execute()
        {
            foreach (Player player in game.getPlayers())
            {
                if (player.isLocalPlayer && !GameManager.Instance.isServerAuthoritative) continue;
                MainThreadDispatcher.Instance.EnqueueAction(player.UpdateGameObject);
            }
        }
    }
}