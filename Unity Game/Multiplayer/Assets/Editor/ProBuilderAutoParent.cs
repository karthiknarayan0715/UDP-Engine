using UnityEditor;
using UnityEngine;
using UnityEngine.ProBuilder;

[InitializeOnLoad]
public class ProBuilderAutoParent
{
    private static readonly string parentName = "Map"; // Parent GO Name

    static ProBuilderAutoParent()
    {
        // Listen for selection changes
        Selection.selectionChanged += OnSelectionChanged;
    }

    private static void OnSelectionChanged()
    {
        GameObject[] selectedObjects = Selection.gameObjects;

        foreach (GameObject obj in selectedObjects)
        {
            if (obj.GetComponent<ProBuilderMesh>() != null) // Check if it's a ProBuilder object
            {
                AssignToParent(obj);
            }
        }
    }

    private static void AssignToParent(GameObject obj)
    {
        GameObject parent = GameObject.Find(parentName);

        // Create parent if it doesn't exist
        if (parent == null)
        {
            parent = new GameObject(parentName);
            Debug.Log($"Created new parent object: {parentName}");
        }

        // If it's not already parented, move it
        if (obj.transform.parent != parent.transform)
        {
            Undo.SetTransformParent(obj.transform, parent.transform, "Auto-Parent ProBuilder Object");
            Debug.Log($"Moved '{obj.name}' under '{parentName}'");
        }
    }
}