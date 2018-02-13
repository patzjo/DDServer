#pragma once

#include <list>
#include <string>


namespace DDServer 
{
    class Client
    {
        public:


        private:
            void getMessages();                     // Get all messages to this client
            std::string accountName;                // Account name
            unsigned long long playerID;            // GUID string for user account ( unique )
    };

}