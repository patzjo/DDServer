#include "ClientDriver.hpp"

#include "Client.hpp"

void ClientDriver::broadCastMessage(std::string message )
{
    for ( auto& item : messages)
    {
        item.second.push(message);
    }
}

std::queue <std::string>ClientDriver::deliverMessages(int id)
{
    std::lock_guard<std::mutex> lock(messageLock);
    std::queue <std::string> result = messages[id];
    std::queue <std::string> empty;

    std::swap(messages[id], empty);
    return result;
}

void ClientDriver::launchClient(std::string ip, int port)
{
    std::unique_ptr<Client> newClient = std::make_unique<Client>(this, nextID++, ip, port);
//    Client *newClient = new Client(this, nextID++, ip, port);
    
    threads.push_back(std::thread([&]() { newClient->run(); }));
    clients.push_back(std::move(newClient));
}

void ClientDriver::joinAll()
{
    std::for_each(threads.begin(), threads.end(), [](std::thread& t){ t.join(); });
}
