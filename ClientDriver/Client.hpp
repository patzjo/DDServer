#pragma once

#include <string>
#include <queue>

#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

class ClientDriver;
class Client
{
public:
    Client(ClientDriver *drv, int ID, std::string IP, int PORT);
    
    void run();
    void getMessages();
private:
    int clientID = 0;
    bool establishConnection();

    struct sockaddr_in address = {0};
    int sock = 0, valread;
    struct sockaddr_in serv_addr = {0};
    bool connected = false;
    
    std::string ip;
    int port;

    std::queue <std::string> messages;

    ClientDriver *driver = nullptr;
};

