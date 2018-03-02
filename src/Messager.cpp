#include "Messager.hpp"

namespace DDServer
{
    void Messager::sendMessage( ServerMessage msg )
    {
        std::lock_guard<std::mutex> lock(messagerMutex); // Lock from other threads
        messages[msg.targetID].push_back(msg);
    }

    void Messager::sendMessage( unsigned long long to, std::string msg, Client *from)
    {
        std::lock_guard<std::mutex> lock(messagerMutex); // Lock from other threads
        ServerMessage message {to, msg, from};
        messages[to].push_back(message);
    }


    std::list <ServerMessage> Messager::getMessages(unsigned long long targetID)
    {
        std::lock_guard<std::mutex> lock(messagerMutex); // Lock from other threads
        std::list <ServerMessage> result;
        for ( auto& item : messages[targetID])
            result.push_back(item);

    }
}