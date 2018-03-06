#include <iostream>
#include <strings.h>
#include <arpa/inet.h>
#include "ServerListener.hpp"
#include <sstream>

#include <sys/time.h>
#include <sys/socket.h>

namespace DDServer
{
    ServerListener::ServerListener(int PortNum, int MaxQueue, int MaxConnections) : portNum(PortNum), maxQueue(MaxQueue), maxConnections(MaxConnections) 
    {
        allSockets = new int[maxConnections];
        if ( allSockets == nullptr )
        {
            log->push("Can't reserve memory for sockets.");
            exit(EXIT_FAILURE); // TODO(jonne): Should create exit that shutdowns all in a nice way
        }

        for(int c = 0; c < maxConnections; c++)
            allSockets[c] = 0;  // Reset sockets to zero
    }    


    void ServerListener::setLog(Log *logClass) 
    { 
        log = logClass; 
    }

    void ServerListener::start()
    {
        log->push("Starting listener.");
        masterSocket = socket(AF_INET, SOCK_STREAM, 0);
        if ( masterSocket < 0 )
        {
//            std::cerr << "Error opening socket!" << std::endl;
            log->push("ERROR: Unable to open socket!");
        }
        bzero((char *) &serverAddress, sizeof(serverAddress));
        
        serverAddress.sin_family = AF_INET;
        serverAddress.sin_addr.s_addr = INADDR_ANY;
        serverAddress.sin_port = htons(portNum);

        log->push("TRYING: Binding socket.");
        if (bind(masterSocket, (struct sockaddr *) &serverAddress, sizeof(serverAddress)) < 0)
        {
//            std::cerr << "Error on binding!" << std::endl;
            log->push("ERROR: Unable to bind socket!");
            return;
        }

        listen(masterSocket, maxQueue);
        len = sizeof(clientAddress);
        log->push("Starting to listen for clients.");
        std::cout << "Listening... " << std::endl;
        
        if ( threads == nullptr )
        {
//            std::cerr << "CRITICAL: Threads not initialized!" << std::endl;
            log->push("CRITICAL: Threads not initialized!");
            exit(EXIT_FAILURE);
        }



        // We should create some sort of authenticator server, but keeping this simple for now
        fd_set readfds;
        int maxSD = 0;
        char buffer[1024];

        while(1)
        {
            FD_ZERO(&readfds);
            FD_SET(masterSocket, &readfds);
            maxSD = masterSocket;

            for( int c = 0; c < maxConnections; c++)
            {
                int sd = allSockets[c];
                if (sd > 0)
                    FD_SET(sd, &readfds);

                if (sd > maxSD)
                    maxSD = sd;
            }

            int activity = select( maxSD + 1, &readfds, NULL, NULL, NULL);
    
            if ((activity < 0) && (errno != EINTR))
            {
                log->push("select error (main connection loop)");
            }

            if( FD_ISSET(masterSocket, &readfds))
            {
                clientSocket = accept(masterSocket, (struct sockaddr *)&clientAddress, &len);
                if (clientSocket < 0)
                {
                    log->push("Error accepting client." + std::to_string(clientSocket));
                    exit(EXIT_FAILURE);
                }
                
                std::stringstream ss;

                ss << "Client connected. (fd: " << clientSocket << ", ip: " << inet_ntoa(clientAddress.sin_addr) << ", port: " << ntohs(clientAddress.sin_port) << ")";
                log->push(ss.str());


                for( int c = 0; c < maxConnections; c++)
                {
                    if ( allSockets[c] == 0 )
                    {
                        allSockets[c] = clientSocket;   // Adding to sockets.
                        break;
                    }
                }
            }

            for( int c = 0; c < maxConnections; c++)
            {
                int sd = allSockets[c];
                int valRead = 0;

                if (FD_ISSET(sd, &readfds))
                {  
                    if ((valRead = read(sd, buffer, 1024)) == 0)
                    {
                        getpeername(sd, (struct sockaddr*)&clientAddress, &len);
                        std::stringstream ss;

                        ss << "Client disconnected. (ip: " << inet_ntoa(clientAddress.sin_addr) << ", port: " << ntohs(clientAddress.sin_port) << ")";
                        log->push(ss.str());

                        close(sd);
                        allSockets[c] = 0;
                    }
                    else
                    {
                        buffer[valRead] = '\0';
                        std::cout << "Got data: '" <<  buffer << "'" << std::endl;
                        // handle messaging to clients
                    }
                }
            }
/*
            char str[INET_ADDRSTRLEN];
            std::cout << "Threads idle: " << threads->n_idle() << std::endl;

            clientSocket = accept(masterSocket, (struct sockaddr*) &clientAddress, &len);
            
            if ( clientSocket < 0)
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
*/            
            // TODO(Jonne): Send client to the lobby
            
            
       }
    }

}