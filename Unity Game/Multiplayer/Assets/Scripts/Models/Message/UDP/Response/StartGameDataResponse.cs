using System;
using GameScripts;
using Models.GameData;
using UnityEngine;

namespace Models.Message.UDP.Response
{
    public class StartGameDataResponse
    {
        private Game game;
        public StartGameDataResponse(string response)
        {
            CreateGame(response);
        }
        void CreateGame(string response)
        {
            Debug.Log("Raw Response: " + response);
            game = new Game(Guid.Empty.ToString());
            if (response.Equals(String.Empty))
            {
                return;
            }
            string[] playersString = response.Split(';');
            foreach (string playerString in playersString)
            {
                string[] processString = playerString.Split(':');
                string clientId = processString[0];
                string[] processSubString = processString[1].Split('|');
                string position = processSubString[0];
                string speed = processSubString[1];
                string playerRotation = processSubString[2];
                string cameraRotation = processSubString[3];
                string health = processSubString[4];
                Player player = new Player(clientId, "username", 0, false, Utils.Utils.getVector3FromString(position), Utils.Utils.getVector3FromString(speed), Utils.Utils.getVector3FromString(playerRotation), Utils.Utils.getVector3FromString(cameraRotation), float.Parse(health));
                game.AddPlayer(player);
            }
        }

        public void execute()
        {
            Debug.Log("Players in game before setting GameManager: " + game.getPlayers().Count);

            GameManager.Instance.SetCurrentGame(game);
            game.SpawnAllPlayers();
        }
    }
}