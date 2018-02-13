#pragma once
#include <vector>
#include <string>

#include <unistd.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

namespace DDServer
{
    class Communication
    {
    public:
        std::vector <std::string> getNetData();
    private:
        int socketID;                           // Which socket this client have
        struct sockaddr_in clientAddress;       // ClientAddress, ip
        std::vector <std::string> data;
    };
}