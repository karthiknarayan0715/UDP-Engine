using System.Linq;
using UnityEngine;

namespace Models.Message.UDP.Request
{
    public class AuthorizationMessage : UdpMessage
    {
        private string userId;
        private string gameId;
        
        public AuthorizationMessage(string userId, string gameId) {
            this.userId = userId;
            this.gameId = gameId;
        }

        public string getMessage()
        {
            Debug.Log($"userId: {userId}, gameId: {gameId}");
            return userId + gameId;
        }
    }
}