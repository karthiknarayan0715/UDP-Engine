﻿using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MainThreadDispatcher : MonoBehaviour
{
    private static readonly Queue<Action> _actions = new Queue<Action>();

    private static readonly Queue<IEnumerator> _coroutines = new Queue<IEnumerator>();

    public static MainThreadDispatcher Instance;

    public bool IsInstantiated = false;

    public void Start()
    {
        if (Instance == null)
        {
            Instance = this;
            DontDestroyOnLoad(this);
        }
        else
        {
            Destroy(this);
        }
        
        IsInstantiated = true;
    }

    public void EnqueueCoroutine(IEnumerator coroutine)
    {
        lock (_coroutines)
        {
            _coroutines.Enqueue(coroutine);
        }
    }

    public void EnqueueAction(Action action)
    {
        lock (_actions)
        {
            _actions.Enqueue(action);
        }
    }

    private void Update()
    {
        lock (_actions)
        {
            while (_actions.Count > 0)
            {
                _actions.Dequeue().Invoke();
            }
        }

        lock (_coroutines)
        {
            while ((_coroutines.Count > 0))
            {
                StartCoroutine(_coroutines.Dequeue());
            }
        }
    }
}