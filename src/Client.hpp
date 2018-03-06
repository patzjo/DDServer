#pragma once

#include <list>
#include <string>


namespace DDServer 
{
    class Client
    {
        public:


        private:
            class Account account;
            void getMessages();                     // Get all messages to this client
            std::string accountName;                // Account name
            class Messager *messager;               // 

    };

}