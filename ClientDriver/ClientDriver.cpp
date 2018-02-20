#include <iostream>
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

void ClientDriver::sendMessage(int target, std::string message)
{
    messages[target].push(message);
}

void ClientDriver::processMessages()
{
    std::lock_guard<std::mutex>lockMessage(messageLock);
    std::lock_guard<std::mutex>lockRemove(removeListLock);
    
    while(!removeList.empty())
    {
        std::tuple <int, std::thread::id> rm = removeList.front();
        removeClient(std::get<0>(rm), std::get<1>(rm));
        removeList.pop();
    }

    while(!messages[0].empty())
    {
        std::string msg = messages[0].front();

        if ( msg == "needJoin")
        {
            std::cout << "\n\tThread need joining!" << std::endl;
        }
        else
        {
            std::cout << "\n\t" << msg << std::endl;
        }

        messages[0].pop();
    }
}


void ClientDriver::showClients()
{
    for ( auto &c : clients)
    {
        std::cout << "ID #" << c->getID() << ": " << c->threadID << std::endl;
    }
}

void ClientDriver::removeClient(int id, std::thread::id tID)
{
//    std::lock_guard<std::mutex>lock(removeListLock);
    for(auto iterator = threads.begin(); iterator != threads.end();)
    {
        if(iterator->get_id() == tID)
        {
            iterator->join();
            iterator = threads.erase(iterator);
        }
        else
            iterator++;
    }
    for ( auto iterator = clients.begin(); iterator != clients.end(); )
    {
        if(iterator->get()->getID() == id)
            iterator = clients.erase(iterator);
        else
            ++iterator;
    }
}

void ClientDriver::queToRemove(int id, std::thread::id tID)
{
    std::lock_guard<std::mutex>lock(removeListLock);
    removeList.push(std::make_tuple(id, tID));
}
