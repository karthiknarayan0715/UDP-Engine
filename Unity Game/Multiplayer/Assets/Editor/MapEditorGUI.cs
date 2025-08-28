using UnityEditor;
using UnityEngine;

public class SelectionEditorWindow : EditorWindow
{
    private string text;
    private GameObject selected;
    private string transformInfo;

    [MenuItem("Window/Selection Viewer")]
    public static void ShowWindow()
    {
        GetWindow<SelectionEditorWindow>("Selection Viewer");
    }

    private void OnEnable()
    {
        Selection.selectionChanged += OnSelectionChanged;
        OnSelectionChanged();
    }

    private void OnDisable()
    {
        Selection.selectionChanged -= OnSelectionChanged;
    }

    private void OnSelectionChanged()
    {
        selected = Selection.activeGameObject;
        transformInfo = selected != null ? selected.transform.ToString() : "None";
        Repaint();
    }

    private void OnGUI()
    {
        GUILayout.Space(10);
        GUILayout.Label("🗺️ MAP EDITOR", new GUIStyle(EditorStyles.boldLabel) { fontSize = 14, alignment = TextAnchor.MiddleCenter });

        GUILayout.Space(10);

        EditorGUILayout.BeginVertical("box");
        GUILayout.Label("Map Settings", EditorStyles.boldLabel);

        text = EditorGUILayout.TextField("Map Name:", text);

        GUILayout.Space(5);
        if (GUILayout.Button("📤 Export Map", GUILayout.Height(30)))
        {
            MapExporter.ExportMap(text);
        }
        EditorGUILayout.EndVertical();
        EditorGUILayout.LabelField("Selected Object", EditorStyles.boldLabel);
        GUILayout.Space(5);

        if (selected != null)
        {
            EditorGUILayout.LabelField("Transform", transformInfo, EditorStyles.helpBox);
            GUILayout.Space(5);

            if (GUILayout.Button("📤 Export Selected", GUILayout.Height(30)))
            {
                MapExporter.ExportGameObject(selected);
            }
        }
        else
        {
            EditorGUILayout.LabelField("No object selected.");
        }
    }
}



// Optional: Add list of objects if needed
// if (mapObjects.Count > 0)
// {
//     EditorGUILayout.LabelField("Objects in Map:", EditorStyles.boldLabel);
//     scrollPosition = EditorGUILayout.BeginScrollView(scrollPosition, GUILayout.Height(150));
//
//     foreach (var obj in mapObjects)
//     {
//         EditorGUILayout.LabelField("• " + obj.name);
//     }
//
//     EditorGUILayout.EndScrollView();
// }
// else
// {
//     EditorGUILayout.HelpBox("No objects in the scene. Add objects to the map.", MessageType.Info);
// }

// private void DrawSelected(GameObject selectedObject)
// {
//     EditorGUILayout.BeginVertical("box");
//     GUILayout.Label(selectedObject.name, EditorStyles.boldLabel);
//
//     EditorGUI.BeginChangeCheck();
//
//     Vector3 newPosition = EditorGUILayout.Vector3Field("Position", selectedObject.transform.position);
//     Vector3 newScale = EditorGUILayout.Vector3Field("Scale", selectedObject.transform.localScale);
//     Vector3 newRotation = EditorGUILayout.Vector3Field("Rotation", selectedObject.transform.rotation.eulerAngles);
//
//     if (EditorGUI.EndChangeCheck())
//     {
//         Undo.RecordObject(selectedObject.transform, "Modify Object Transform");
//         selectedObject.transform.position = newPosition;
//         selectedObject.transform.localScale = newScale;
//         selectedObject.transform.rotation = Quaternion.Euler(newRotation);
//     }
//
//     if (GUILayout.Button("Delete", GUILayout.Width(80)))
//     {
//         Undo.DestroyObjectImmediate(selectedObject);
//         mapObjects.Remove(selectedObject);
//         EditorGUILayout.EndVertical();
//         GUILayout.Space(5);
//     }
//
//     EditorGUILayout.EndVertical();
//     GUILayout.Space(5);
// }
//
// private void CreateCube()
// {
//     GameObject cube = GameObject.CreatePrimitive(PrimitiveType.Cube);
//     cube.name = "Cube_" + mapObjects.Count;
//     cube.transform.position = Vector3.zero;
//     Undo.RegisterCreatedObjectUndo(cube, "Create Cube");
//     Selection.activeGameObject = cube;
//     mapObjects.Add(cube);
// }
//
// private void ExportMap()
// {
//     Debug.Log("Exporting Map!");
//     // Placeholder for export logic
// }



// GUILayout.Space(10);
// GUILayout.Label("Map Editor", EditorStyles.boldLabel);
// GUILayout.Space(5);
//
// EditorGUILayout.HelpBox("Manage objects in the scene. Modify their properties and export the map.", MessageType.Info);
//
// GUILayout.Space(10);
//
// if (GUILayout.Button("Create Cube", GUILayout.Height(30)))
// {
//     CreateCube();
// }
//
// GUILayout.Space(10);
//
// selectedObjectIndex = EditorGUILayout.Popup("Show Selected:", selectedObjectIndex, objectOptions);
//
// GameObject selectedObject = Selection.activeGameObject;
//
// if (selectedObjectIndex == 0)
// {
//     if (selectedObject == null) return;
//     Selection.selectionChanged += () =>
//     {
//         selectedObject = Selection.activeGameObject;
//         Repaint();
//     };
//     DrawSelected(selectedObject);
// }
// else
// {
//     if (mapObjects.Count > 0)
//     {
//         scrollPosition = EditorGUILayout.BeginScrollView(scrollPosition, GUILayout.Height(300));
//
//         foreach (var mapObject in mapObjects)
//         {
//             if (mapObject == null) continue;
//
//             DrawSelected(mapObject);
//         }
//
//         EditorGUILayout.EndScrollView();
//     }
//     else
//     {
//         EditorGUILayout.HelpBox("No objects in the scene. Click 'Create Cube' to add one!", MessageType.Warning);
//     }
// }
//
// GUILayout.Space(10);