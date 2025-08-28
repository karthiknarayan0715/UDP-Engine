using UnityEngine;

namespace Utils
{
    public class Utils
    {
        public static Vector3 getVector3FromString(string vector3String)
        {
            string[] vector3 = vector3String.Split(',');
            return new Vector3(float.Parse(vector3[0]), float.Parse(vector3[1]), float.Parse(vector3[2]));
        }
    }
}