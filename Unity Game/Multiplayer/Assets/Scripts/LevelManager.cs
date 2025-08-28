using System;
using UnityEngine;
using UnityEngine.SceneManagement;

public class LevelManager : MonoBehaviour
{
    public static LevelManager Instance;
    public void Start()
    {
        if (Instance != null)
        {
            Destroy(this.gameObject);
        }
        DontDestroyOnLoad(this);
        Instance = this;
    }

    public void LoadGameScene()
    {
        SceneManager.LoadSceneAsync(1);
    }
}
