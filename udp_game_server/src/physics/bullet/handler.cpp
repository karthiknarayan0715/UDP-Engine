// #include "physics/bullet/handler.h"
// #include <fstream>
// #include <iostream>
// #include <nlohmann/json.hpp>

// using json = nlohmann::json;

// bool LoadMeshFromJson(const std::string& filename, std::vector<MeshObject>& objects) {
//     std::ifstream file("static/"+filename);
//     if (!file.is_open()) {
//         std::cerr << "Failed to open " << filename << std::endl;
//         return false;
//     }

//     json jsonData;
//     file >> jsonData;
//     file.close();

//     for (const auto& obj : jsonData["objects"]) {
//         MeshObject mesh;
//         mesh.name = obj["name"];
//         mesh.position = {obj["position"]["x"], obj["position"]["y"], obj["position"]["z"]};
//         mesh.rotation = {obj["rotation"]["x"], obj["rotation"]["y"], obj["rotation"]["z"]};
//         mesh.scale = {obj["scale"]["x"], obj["scale"]["y"], obj["scale"]["z"]};

//         for (const auto& vert : obj["meshVertices"]) {
//             Vector3 adjustedVertex = Vector3(
//                 vert["x"].get<float>(),
//                 vert["y"].get<float>(),
//                 vert["z"].get<float>()
//             );
//             mesh.vertices.push_back(adjustedVertex);
//         }        

//         for (const auto& idx : obj["meshTriangles"]) {
//             mesh.indices.push_back(idx);
//         }

//         objects.push_back(mesh);
//     }

//     return true;
// }

// bool LoadObjectFromJson(const std::string& filename, MeshObject& object) {
//     std::vector<MeshObject> temp_objects;
//     if(LoadMeshFromJson(filename, temp_objects)) {
//         object = temp_objects[0];
//         return true;
//     }
//     return false;
// }