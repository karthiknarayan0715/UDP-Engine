using System.Collections;
using System.Collections.Generic;
using GameScripts;
using Models.GameData;
using Models.MetaData;
using Models.UserData;
using Static;
using TMPro;
using Unity.VisualScripting;
using UnityEngine;

public class GameManager : MonoBehaviour
{
    public bool testing = false;
    public static GameManager Instance { get; private set; }
    public bool IsInitialized = false;
    public GameState _gameState = GameState.LOGIN;
    
    private UserData _userData;
    private GameData _gameData;
    
    private Player _player;
    private Game _game;

    [SerializeField] private string GameID;
    
    [SerializeField] private TMP_Text userIdText;
    
    [SerializeField] public bool isServerAuthoritative = true;

    IEnumerator Start()
    {
        while (MainThreadDispatcher.Instance == null || MainThreadDispatcher.Instance.IsInstantiated == false)
        {
            yield return null;
        }

        if (Instance == null)
        {
            Instance = this;
            DontDestroyOnLoad(this);
        }
        else
        {
            Destroy(this);
        }

        _userData = new UserData();

        if (!testing)
        {
            userIdText.SetText("User ID: " + _userData.getUUID());
            this.changeGameState(GameState.LOGIN);
        }
        else
        {
            this.changeGameState(GameState.IN_GAME);
        }

        Cursor.lockState = CursorLockMode.Locked;
        Cursor.visible = false;
        
        IsInitialized = true;
    }

    public void changeGameState(GameState newGameState)
    {
        this._gameState = newGameState;
        switch (newGameState)
        {
            case GameState.LOGIN:
                MainThreadDispatcher.Instance.EnqueueAction(() =>
                {
                    StartCoroutine(UiManager.Instance.UpdateCanvas(GameState.LOGIN));
                });
                break;
            case GameState.LOBBY:
                MainThreadDispatcher.Instance.EnqueueAction(() =>
                {
                    StartCoroutine(UiManager.Instance.UpdateCanvas(GameState.LOBBY));
                });
                break;
        }
    }
    
    public UserData getUserData()
    {
        return _userData;
    }

    public void SetGameData(GameData gameData)
    {
        this._gameData = gameData;
    }
    
    public GameData GetGameData()
    {
        return _gameData;
    }

    public Game GetCurrentGame()
    {
        return _game;
    }
    
    public void SetCurrentGame(Game _game)
    {
        Debug.Log(_game.gameId);
        this.GameID = _game.gameId;
        this._game = _game;
    }
    
}
