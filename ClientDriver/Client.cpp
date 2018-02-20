#include <iostream>

#include "Client.hpp"
#include "ClientDriver.hpp"

Client::Client(ClientDriver *drv, int ID, std::string IP, int PORT)
{
    driver = drv;
    clientID = ID;
    ip = IP;
    port = PORT;
}

void Client::getMessages()
{
    if (driver == nullptr)
        return;

    std::queue <std::string> newMessages = driver->deliverMessages(clientID);
    
    if (newMessages.empty())
    {
        return;
    }
    
    if ( messages.empty() )
    {
        messages = newMessages;
        return;
    }

    while(!newMessages.empty())
    {
        messages.push(newMessages.front());
        newMessages.pop();
    }
}

void Client::run()
{
    if (!establishConnection())
    {
        std::cerr << "\n: Cant Connect!" << std::endl;
        return;
    }
    
    bool done = false;
    while(!done)
    {
        getMessages();
        while(!messages.empty())
        {
            std::cout << "Client ID: " << clientID << "Received:\n\t" << messages.front() << std::endl;
            
            if ( messages.front() == "shutdown")
            {
                done = true;
                break;
            }

            

            messages.pop();
        }

        sleep(1);
    }

    std::cout << "Shuttingdown: " << clientID << std::endl;
}

bool Client::establishConnection()
{
    if((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        std::cerr << "\nError while creating socket." << std::endl;
        return false;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);

    if(inet_pton(AF_INET, ip.c_str(), &serv_addr.sin_addr) <= 0)
    {
        std::cerr << "\nInvalid address." << std::endl;
        return false;
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        std::cerr << "\nConnection failed!" << std::endl;
        return false;
    }

}
