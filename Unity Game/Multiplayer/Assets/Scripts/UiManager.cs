using System;
using System.Collections;
using System.Collections.Generic;
using Static;
using TMPro;
using Unity.VisualScripting;
using UnityEngine;
using UnityEngine.Serialization;
using UnityEngine.UI;

public class UiManager : MonoBehaviour
{

    public static UiManager Instance { get; private set; }

    [SerializeField] private Canvas loginCanvas;

    [SerializeField] private Canvas lobbyCanvas;

    [SerializeField] private Button lookingForMatchButton;

    [SerializeField] private TMP_Text lookingForMatchText;

    [SerializeField] private Button cancelMatchRequestButton;

    [SerializeField] private TMP_Text usernameText;

    private Dictionary<GameState, Canvas> gameStateCanvasMap;

    private int waitTime;
    
    public bool matchFound;

    private bool matchRequestCancelled;

    public void Awake()
    {
        if (UiManager.Instance != null)
        {
            Destroy(UiManager.Instance.GameObject());
        }

        UiManager.Instance = this;
        gameStateCanvasMap = new Dictionary<GameState, Canvas>
        {
            { GameState.LOGIN, loginCanvas },
            { GameState.LOBBY, lobbyCanvas }
        };
    }

    public void ConnectToServer()
    {
        Debug.Log(TcpNetworkManager.Instance);
        TcpNetworkManager.Instance.ConnectToServer(usernameText.GetParsedText());
    }

    public IEnumerator UpdateCanvas(GameState gameState)
    {
        yield return null;
        foreach (GameState state in gameStateCanvasMap.Keys)
        {
            gameStateCanvasMap[state].GameObject().SetActive(state.Equals(gameState));
        }
    }

    public void StartMatchSearch()
    {
        lookingForMatchButton.interactable = false;
        matchFound = false;
        matchRequestCancelled = false;
        waitTime = 0;
        lookingForMatchText.alignment = TextAlignmentOptions.Left;
        lookingForMatchText.fontSize = 24;
        lookingForMatchText.margin = new Vector4(15, 0, 0, 0);
        cancelMatchRequestButton.GameObject().SetActive(true);
        StartCoroutine(UpdateLookingForMatchTimer());
    }

    public void CancelMatchRequest()
    {
        lookingForMatchButton.interactable = true;
        lookingForMatchText.alignment = TextAlignmentOptions.Center;
        lookingForMatchText.fontSize = 26;
        lookingForMatchText.margin = new Vector4(0, 0, 0, 0);
        lookingForMatchText.text = "START";
        cancelMatchRequestButton.GameObject().SetActive(false);
        matchRequestCancelled = true;
    }

    private IEnumerator UpdateLookingForMatchTimer()
    {
        while (!(matchFound || matchRequestCancelled))
        {
            lookingForMatchText.text = waitTime / 60 + " : " + (waitTime % 60).ToString("D2");
            waitTime++;
            yield return new WaitForSeconds(1);
        }
    }

}
