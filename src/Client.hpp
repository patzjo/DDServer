#pragma once

#include <list>
#include <string>

#include <unistd.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

namespace DDServer 
{
    class Client
    {
        public:


        private:
            void getMessages();                     // Get all messages to this client
            int socketID;                           // Which socket this client have
            struct sockaddr_in clientAddress;       // ClientAddress, ip
            std::string accountName;                // Account name
            unsigned long long playerID;            // GUID string for user account ( unique )
    };

}