# UDP Engine

A C++ engine for real-time multiplayer games, designed around an **authoritative server** model using an **Entity Component System (ECS) architecture** and a **custom UDP networking layer**.

---

## **Features**
- **UDP Networking Layer** – Custom UDP network layer to handle messages between the game client and the server.  
- **Entity Component System (ECS)** – Modular architecture that keeps gameplay logic flexible and reusable.  
- **Authoritative Server** – The server handles all core game logic, preventing client-side exploits.  
- **100+ Concurrent Players** – Stress-tested with 100+ concurrent players, with negligible impact on framerate.  

---

## **Tech Stack**
- **Language:** C++17 (or newer)  
- **Networking:** Custom UDP layer (`sys/socket.h`)  
- **Architecture:** Entity Component System (ECS), Authoritative Server  
- **Build System:** Makefile  
- **Tested On:** Debian (via WSL)  

---

## **How to Run**

### **Server**
1. Make sure you are running Linux (WSL works).  
2. Run the following commands:
   ```bash
   cd udp_game_server
   make clean run
   make start
    ```

### **Server**
1.	Install Unity Engine and open the project in the Unity Game/ folder.
2.	Ensure the server is running.
3.	Press Play inside the Unity Editor.