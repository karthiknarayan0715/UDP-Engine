#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

class AuthorizationRequest;
class Vector3;
class Game;

void HandleAuthorizationRequest(sockaddr_in clientSocket, AuthorizationRequest request);

void CreatePlayer(Vector3 &spawn_point, sockaddr_in &clientSocket, AuthorizationRequest &request, Game *current_game);
