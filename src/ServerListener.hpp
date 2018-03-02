#pragma once
#include <string>

#include <unistd.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include <iostream>
#include <fstream>
#include <thread>

#include "Log.hpp"
#include "ThreadPool.hpp"

namespace DDServer
{

    class ServerListener
    {
        public:
            ServerListener() : portNum(5550), maxQueue(5), maxConnections(30)
            { 
                allSockets = new int[maxConnections];
                if ( allSockets == nullptr )
                {
                    log->push("Can't reserve memory for sockets.");
                    exit(EXIT_FAILURE); // TODO(jonne): Should create exit that shutdowns all in nice way
                }

                for(int c = 0; c < maxConnections; c++)
                    allSockets[c] = 0;  // Reset sockets to zero
               
            }
            ServerListener(int PortNum, int MaxQueue = 10, int MaxConnections = 30);
            ~ServerListener() {
                close(masterSocket);
            }
            void start();
            void setPort(int num) {portNum=num;}

            void setLog(Log *logClass);
            void setThreads(ctpl::ThreadPool *myThreads) { threads = myThreads; }
        private:
            int masterSocket, portNum, clientSocket, maxQueue, maxConnections;
            socklen_t len;
            struct sockaddr_in serverAddress, clientAddress;
            ctpl::ThreadPool *threads = nullptr;
            
            int *allSockets = nullptr;
            Log *log        = nullptr;
            
    };

}