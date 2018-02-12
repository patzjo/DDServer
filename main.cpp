/*
    Should implement
        - verification to join server.
        - Some kind of data crypting
        - mariaDB integration
*/

#include <iostream>


#include "src/ThreadPool.hpp"
#include "src/ServerListener.hpp"
#include "src/Client.hpp"
#include "src/Server.hpp"
#include "src/Log.hpp"

int main( int argc, char **argv )
{
    DDServer::Server server(550, 100);
    DDServer::Log serverLog("server.log");

    std::cout << "Starting server." << std::endl;
    server.setLog(&serverLog);
    server.startListening();
    
    std::cin.get();
    return 0;
}