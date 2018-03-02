#pragma once

#include <string>
#include <map>
#include <mutex>
#include "Client.hpp"

namespace DDServer
{

    // Using struct now, so i can easily change it to reflect all data i need.
    struct ServerMessage
    {
        unsigned long long targetID;
        std::string message;
        Client *sender;
    };

    class Messager
    {
    public:

        void sendMessage( ServerMessage msg );
        void sendMessage( unsigned long long targetID, std::string msg, Client *from);
        std::list <ServerMessage> getMessages(unsigned long long targetID); // Request all messages of targetID
    
    private:
        std::map <unsigned long long, std::list <ServerMessage>>messages;
        std::mutex messagerMutex;
    };


}