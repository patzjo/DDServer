#pragma once

#include <string>
#include <map>
#include <mutex>
#include "Client.hpp"

namespace DDServer
{

    struct ServerMessage
    {
        unsigned long long targetID;
        std::string message;
        Client *sender;
    };

    class Messager
    {
    public:
        void sendMessage( unsigned long long targetID, ServerMessage msg);
        std::list <ServerMessage> getMessages(unsigned long long targetID);
    
    private:
        std::map <unsigned long long, std::list <ServerMessage>>messages;
        std::mutex messagerMutex;
    };


}