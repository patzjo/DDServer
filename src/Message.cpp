#include "Message.hpp"

namespace DDServer
{
    void Messager::sendMessage( unsigned long long targetID, ServerMessage msg)
    {
        std::lock_guard<std::mutex> lock(messagerMutex); // Lock from other threads
        messages[targetID].push_back(msg);
    }


    std::list <ServerMessage> Messager::getMessages(unsigned long long targetID)
    {
        std::lock_guard<std::mutex> lock(messagerMutex); // Lock from other threads
        std::list <ServerMessage> result;
        for ( auto& item : messages[targetID])
            result.push_back(item);

    }
}