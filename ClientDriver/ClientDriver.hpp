#pragma once

#include <thread>
#include <mutex>
#include <queue>
#include <map>
#include <memory>
#include <thread>
#include <algorithm>
#include <string>
#include <tuple>

class Client;
class ClientDriver
{
public:
    std::queue <std::string> deliverMessages(int id);    
    void processMessages();
    void launchClient(std::string ip, int port);
    void joinAll();

    void showClients();

    void broadCastMessage(std::string message);
    void sendMessage(int target, std::string message);
    void queToRemove(int id, std::thread::id tID);

private:
    void removeClient(int id, std::thread::id tID);
    std::vector <std::unique_ptr<Client>> clients;
    std::vector <std::thread> threads;
    std::map    <int, std::queue <std::string>> messages;
    std::queue <std::tuple<int, std::thread::id>> removeList;
    
    int nextID = 1; // Driver has id 0 reserved
    std::mutex messageLock;
    std::mutex removeListLock;
};

