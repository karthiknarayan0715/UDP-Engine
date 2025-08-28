using UnityEngine;

namespace GameScripts
{
    public class Player
    {
        public string clientId { get; set; }
        public string username { get; set; }
        public int team { get; set; }
        public bool isLocalPlayer { get; set; }
        
        public Vector3 position { get; set; }
        public Vector3 speed { get; set; }
        public Vector3 playerRotation { get; set; }
        public Vector3 cameraRotation { get; set; }
        
        public GameObject playerGameObject { get; set; }
        
        public GameObject playerCameraGameObject { get; set; }

        public float health { get; set; }
        
        public Player(string clientId, string username, int team, bool isLocalPlayer, Vector3 position, Vector3 speed, Vector3 playerRotation, Vector3 cameraRotation, float health)
        {
            this.clientId = clientId;
            this.username = username;
            this.team = team;
            this.isLocalPlayer = isLocalPlayer;
            this.playerRotation = playerRotation;
            this.cameraRotation = cameraRotation;
            this.position = position;
            this.speed = speed;
            this.health = health;
        }
        
        public void SetPlayerGameObject(GameObject obj) {
            playerGameObject = obj;
        }
        
        public void SetPlayerCameraGameObject(GameObject obj) {
            playerCameraGameObject = obj;
        }
        
        public void UpdateGameObject() {
            playerGameObject.transform.position = position;
            if (isLocalPlayer) return;
            playerCameraGameObject.transform.localRotation = Quaternion.Euler(cameraRotation.x, 0, 0);
            playerGameObject.transform.rotation = Quaternion.Euler(playerRotation.x, playerRotation.y, playerRotation.z);
        }
    }
}