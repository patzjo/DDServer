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
            ServerListener() : portNum(550), maxQueue(5) { }
            ServerListener(int PortNum, int MaxQueue = 10) : portNum(PortNum), maxQueue(MaxQueue) { }    
            ~ServerListener() {
                close(sockfd);
            }
            void start();
            void setPort(int num) {portNum=num;}

            void setLog(Log *logClass);
            void setThreads(ctpl::ThreadPool *myThreads) { threads = myThreads; }
        private:
            int sockfd, portNum, newSocket, maxQueue;
            socklen_t len;
            struct sockaddr_in serverAddress, clientAddress;

            ctpl::ThreadPool *threads;

            Log *log;
            
    };

}