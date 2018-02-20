#pragma once

#include <thread>
#include <mutex>
#include <queue>
#include <map>
#include <memory>
#include <thread>
#include <algorithm>
#include <string>

class Client;
class ClientDriver
{
public:
    std::queue <std::string> deliverMessages(int id);    
    void launchClient(std::string ip, int port);
    void joinAll();

    void broadCastMessage(std::string message);

private:
    std::vector <std::unique_ptr<Client>> clients;
    std::vector <std::thread> threads;
    std::map    <int, std::queue <std::string>> messages;

    int nextID = 1;
    std::mutex messageLock;
};

