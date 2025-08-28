using System.Collections.Generic;
using System.IO;
using UnityEngine;
using UnityEditor;

public class MapExporter : EditorWindow
{
    public static void ExportMap(string mapName)
    {
        GameObject mapParent = GameObject.Find("Map");

        if (mapParent.Equals(null))
        {
            Debug.LogError("No GameObject named 'Map' found! Please create a parent GameObject named 'Map'.");
            return;
        }

        List<MapObjectData> mapObjects = new List<MapObjectData>();

        foreach (Transform child in mapParent.transform)
        {
            MeshFilter meshFilter = child.GetComponent<MeshFilter>();
            Mesh mesh = meshFilter ? meshFilter.sharedMesh : null;

            MapObjectData objData = new MapObjectData
            {
                name = child.gameObject.name,
                position = child.position,
                rotation = child.rotation.eulerAngles,
                scale = child.localScale,
                meshVertices = mesh ? mesh.vertices : null,
                meshTriangles = mesh ? mesh.triangles : null
            };

            mapObjects.Add(objData);
        }
        string json = JsonUtility.ToJson(new MapData { objects = mapObjects }, true);
        string filePath = Application.dataPath + "/MapData/map_" + mapName + ".json";

        File.WriteAllText(filePath, json);
        Debug.Log("Map exported to: " + filePath);
        AssetDatabase.Refresh(); // Refresh Unity Asset Database
    }

    public static void ExportGameObject(GameObject gameObject)
    {
        List<MapObjectData> mapObjects = new List<MapObjectData>();
        MeshFilter meshFilter = gameObject.GetComponent<MeshFilter>();
        Mesh mesh = meshFilter ? meshFilter.sharedMesh : null;

        MapObjectData objData = new MapObjectData
        {
            name = gameObject.name,
            position = gameObject.transform.position,
            rotation = gameObject.transform.rotation.eulerAngles,
            scale = gameObject.transform.localScale,
            meshVertices = mesh ? mesh.vertices : null,
            meshTriangles = mesh ? mesh.triangles : null
        };
        
        mapObjects.Add(objData);
        
        string json = JsonUtility.ToJson(new MapData { objects = mapObjects }, true);
        string filePath = Application.dataPath + "/MapData/object" + gameObject.name + ".json";

        File.WriteAllText(filePath, json);
        Debug.Log("Map exported to: " + filePath);
        AssetDatabase.Refresh(); // Refresh Unity Asset Database
    }
    
}

[System.Serializable]
public class MapObjectData
{
    public string name;
    public Vector3 position;
    public Vector3 rotation;
    public Vector3 scale;
    public Vector3[] meshVertices;
    public int[] meshTriangles;
}

[System.Serializable]
public class MapData
{
    public List<MapObjectData> objects;
}