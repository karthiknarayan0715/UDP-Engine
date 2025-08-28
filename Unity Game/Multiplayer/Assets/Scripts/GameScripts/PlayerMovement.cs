using System.Collections;
using System.Collections.Generic;
using System.Text;
using GameScripts;
using Models;
using Models.GameData;
using Models.Message.UDP.Constants;
using Models.Message.UDP.Request;
using Models.UserData;
using Network;
using UnityEngine;
using UnityEngine.Serialization;

public class PlayerMovement : MonoBehaviour
{
    public Player _player;
    
    public bool IsLocalPlayer = false;

    [SerializeField] private float speed;
    
    [SerializeField]
    [Range(0.1f, 10f)]
    private float sensitivityMultiplier = 0.2f;
    
    private float sensitivity = 100f;

    [System.Serializable]
    private class ClampAngles
    {
        public float min = -90;
        public float max = 90;
    } 
    [SerializeField] private ClampAngles clampAngles;

    [SerializeField]
    private GameObject playerCamera;
    
    UdpConnector _udpConnector;
    void Update()
    {
        int moveX = (int) Input.GetAxisRaw("Horizontal");

        int moveZ = (int)Input.GetAxisRaw("Vertical");
        
        float lookX = Input.GetAxis("Mouse X");
        float lookY = -Input.GetAxis("Mouse Y");

        bool isJumping = Input.GetKeyDown(KeyCode.Space);

        bool isShooting = Input.GetKeyDown(KeyCode.Mouse0);
        
        if(!IsLocalPlayer) return;
        Vector3 playerRotationVector = Vector3.zero;
        Vector3 cameraRotationVector = Vector3.zero;

        cameraRotationVector.x = lookY * sensitivity * sensitivityMultiplier * Time.deltaTime;
        playerRotationVector.y = lookX * sensitivity * sensitivityMultiplier * Time.deltaTime;

        Vector3 playerLookAngle = playerRotationVector + transform.rotation.eulerAngles;

        Vector3 currentEulerAngles = playerCamera.transform.localRotation.eulerAngles;
        if (currentEulerAngles.x > 180)
        {
            currentEulerAngles.x -= 360f;
        }
        Vector3 desiredCameraLookAngle = cameraRotationVector + currentEulerAngles;

        Vector3 actualCameraLookAngle = Vector3.zero;

        if (desiredCameraLookAngle.x > clampAngles.max || desiredCameraLookAngle.x < clampAngles.min)
        {
            actualCameraLookAngle.x = Mathf.Clamp(desiredCameraLookAngle.x, clampAngles.min, clampAngles.max);
        }
        else
        {
            actualCameraLookAngle.x = desiredCameraLookAngle.x;
        }

        if (!GameManager.Instance.isServerAuthoritative)
        {
            Vector3 movementVector = Vector3.zero;
            movementVector.x = moveX;
            movementVector.z = moveZ;
            
            movementVector = movementVector.x * transform.right + movementVector.z * transform.forward;
        
            if (movementVector.magnitude > 0)
            {
                movementVector.Normalize();
            }

            movementVector *= speed * Time.deltaTime;

            transform.position += movementVector;
        }


        transform.rotation = Quaternion.Euler(playerLookAngle);
        playerCamera.transform.localRotation = Quaternion.Euler(actualCameraLookAngle.x, 0f, 0f);
        
        if (isShooting)
        {
            Debug.Log("ShootDirection: " + playerCamera.transform.forward);
            Debug.Log("ShootPosition: " + playerCamera.transform.position);
        }
        
        PlayerInputsMessage playerInputsMessage = new PlayerInputsMessage(moveX, moveZ, playerLookAngle, actualCameraLookAngle, isJumping, isShooting);
        UdpRequest request = new UdpRequest(UdpRequestType.INPUT, playerInputsMessage);
        UdpNetworkManager.Instance.SendMessage(request.GetMessage());

    }
}
