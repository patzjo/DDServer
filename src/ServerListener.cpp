#include <iostream>
#include <strings.h>
#include <arpa/inet.h>
#include "ServerListener.hpp"

namespace DDServer
{
    void ServerListener::setLog(Log *logClass) 
    { 
        log = logClass; 
    }

    void ServerListener::start()
    {
        log->push("Starting listener.");
        sockfd = socket(AF_INET, SOCK_STREAM, 0);
        if ( sockfd < 0 )
        {
            std::cerr << "Error opening socket!" << std::endl;
            log->push("ERROR: Unable to open socket!");
        }
        bzero((char *) &serverAddress, sizeof(serverAddress));
        
        serverAddress.sin_family = AF_INET;
        serverAddress.sin_addr.s_addr = INADDR_ANY;
        serverAddress.sin_port = htons(portNum);

        log->push("TRYING: Binding socket.");
        if (bind(sockfd, (struct sockaddr *) &serverAddress, sizeof(serverAddress)) < 0)
        {
            std::cerr << "Error on binding!" << std::endl;
            log->push("ERROR: Unable to bind socket!");
            return;
        }

        listen(sockfd, maxQueue);
        len = sizeof(clientAddress);
        log->push("Starting to listen for clients.");
        std::cout << "Listening... " << std::endl;
        
        if ( threads == nullptr )
        {
            std::cerr << "CRITICAL: Threads not initialized!" << std::endl;
            log->push("CRITICAL: Threads not initialized!");
            exit(1);
        }

        // We should create some sort of authenticator server, but keeping this simple now
        while(1)
        {
            char str[INET_ADDRSTRLEN];
            
            std::cout << "Threads idle: " << threads->n_idle() << std::endl;

            newSocket = accept(sockfd, (struct sockaddr*) &clientAddress, &len);
            if ( newSocket < 0)
            {
                std::cerr << "Error on accept" << std::endl;
                log->push("Cant accept client!");
            }
 
            std::string completeString = "Client ";
            inet_ntop(AF_INET, &(clientAddress.sin_addr), str, INET_ADDRSTRLEN);
            completeString += str;
            completeString += " has been succesfully connected!";
            std::cout << completeString << std::endl;
            log->push(completeString);
            
            // TODO(Jonne): Send to the lobby 
        }
    }

}