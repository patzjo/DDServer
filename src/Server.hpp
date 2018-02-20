#pragma once
#include "ServerListener.hpp"
#include "Client.hpp"
#include "ThreadPool.hpp"
#include "Log.hpp"
#include "Game.hpp"
#include "Message.hpp"

#include <memory>


namespace DDServer
{
    class Server 
    {
    public:
        Server() { threads.resize(10); }
     
        Server(int portNum, int ThreadCount);
        ~Server() {}

        bool startListening();

        void setLog( Log *logClass ) { log = logClass; }
        void startServer();
        void stopServer();

    private:
        ServerListener listener;
        ctpl::ThreadPool threads;
        Log *log;
        Messenger messages;

        std::vector <Client> clients;
        std::vector <std::shared_ptr<DDGame>> games;

        int threadCount = 0;
    };
}