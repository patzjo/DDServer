#include <iostream>
#include <sstream>
#include <chrono>

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
    std::thread::id threadID = std::this_thread::get_id();
    
    this->tID = threadID;
    
        
    if (!establishConnection())
    {
        std::cerr << "\n: Cant Connect!" << std::endl;
    }
    else
    {
        bool done = false;
        while(!done)
        {
            getMessages();
            while(!messages.empty())
            {
                std::string msg = messages.front();
                std::cout << "\nClient ID: " << clientID << " Received:\n\t'" << msg << "'"<< std::endl;
                
                if ( msg == "shutdown")
                {
                    done = true;
                    break;
                }

                if ( msg == "showID")
                {
                    std::stringstream ss;
                    ss << threadID;
                    std::string str = "showIDReply ";
                    str += ss.str();
                    driver->sendMessage(0, str);
                }

                messages.pop();
            }

            //sleep(1);
            using namespace std::chrono_literals;
            std::this_thread::sleep_for(5ms);
        }
    }
/*
    std::stringstream ss;
    ss << "remove " << clientID << " " << threadID << std::endl;
    
    driver->sendMessage(0, ss.str());
*/
    driver->queToRemove(clientID, threadID);
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
        std::cerr << "\nInvalid address. " << ip.c_str() << std::endl;
        return false;
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        std::cerr << "\nConnection failed!" << std::endl;
        return false;
    }

    return true;
}
