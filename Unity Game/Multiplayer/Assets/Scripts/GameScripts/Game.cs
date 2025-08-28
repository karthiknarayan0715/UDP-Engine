using System.Collections.Generic;
using GameScripts;
using UnityEngine;

namespace Models.GameData
{
    public class Game
    {
        public string gameId;
        
        List<Player> players;
        
        public Game(string gameId)
        {
            this.gameId = gameId;
            this.players = new List<Player>();
        }
        
        public List<Player> getPlayers() => players;

        public void AddPlayer(Player player)
        {
            players.Add(player);
        }

        public void SpawnAllPlayers()
        {
            foreach (Player player in players)
            {
                UdpNetworkManager.Instance.SpawnPlayer(player);
            }
        }

        public Player GetPlayerById(string playerId)
        {
            return players.Find(x =>
            {
                // Debug.Log("In find loop: " + x.clientId + ": "+ playerId);
                return x.clientId == playerId;
            });
        }
    }
}