using UnityEngine;

namespace Models.Message.UDP.Request
{
    public class PlayerInputsMessage : UdpMessage
    {
        int moveX, moveZ;
        Vector3 playerRotation;
        Vector3 cameraRotation;
        bool isJumping;
        bool isShooting;
        
        public PlayerInputsMessage(int moveX, int moveZ, Vector3 playerRotation, Vector3 cameraRotation, bool isJumping, bool isShooting) {
            this.moveX = moveX;
            this.moveZ = moveZ;
            this.playerRotation = playerRotation;
            this.cameraRotation = cameraRotation;
            this.isJumping = isJumping;
            this.isShooting = isShooting;
        }

        public string getMessage()
        {
            int isJumping = this.isJumping ? 1 : 0;
            int isShooting = this.isShooting ? 1 : 0;
            string message = GameManager.Instance.getUserData().getUUID() + ":" + moveX + "|" + moveZ + "|" +
                GameUtils.getVector3String(playerRotation) + "|" + GameUtils.getVector3String(cameraRotation) + "|" +
                isJumping + "|" + isShooting;
            return message;
        }
    }
}