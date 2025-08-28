using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class TestingManager : MonoBehaviour
{

    [SerializeField] private GameObject localPlayer;
    IEnumerator Start()
    {
        while (GameManager.Instance == null)
        {
            yield return null;
        }

        GameObject playerInstance = Instantiate(localPlayer, Vector3.zero, Quaternion.identity);
    }
}
