using System.Linq;
using UnityEngine;

namespace Models.Message.UDP.Response
{
    public class SpawnPlayerUdpResponse : BaseUdpResponse
    {
        public Vector3 SpawnPoint;
        public string clientId;
        
        public SpawnPlayerUdpResponse(string response)
        {
            Debug.Log("SpawnPlayerUdpResponse: " + response);
            string clientIdString = response.Split('|')[0].Trim();
            string spawnPointString = response.Split('|')[1].Trim();
            float[] spawnPoint = spawnPointString.Split(',').Select(s=>float.Parse(s.Trim())).ToArray();

            this.clientId = clientIdString;
            this.SpawnPoint = new Vector3(spawnPoint[0], spawnPoint[1], spawnPoint[2]);
        }
    }
}