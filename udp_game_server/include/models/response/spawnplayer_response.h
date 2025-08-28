#include "utils/vector3/vector3.h"

class SpawnPlayerResponse{
    Vector3 spawn_point;
    std::string clientId;
    public:
        SpawnPlayerResponse(Vector3 position, std::string clientId);
        std::string GetMessage();
};