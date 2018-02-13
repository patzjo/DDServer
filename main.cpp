/*
    Should implement
        - verification to join server.
        - Some kind of data crypting
        - mariaDB integration
*/

#include <iostream>
#include <string>
#include <vector>
#include <sstream>

#include <stdio.h>
#include <sys/select.h>
#include <termios.h>

#include "src/ThreadPool.hpp"
#include "src/ServerListener.hpp"
#include "src/Client.hpp"
#include "src/Server.hpp"
#include "src/Log.hpp"



std::vector<std::string> split( std::string str, char sep = ' ' )
{
	std::vector<std::string> result;

	std::istringstream stm(str);
	std::string token;
	while( std::getline( stm, token, sep ) ) result.push_back(token);

	return result;
}

bool processCommand(std::string cmd)
{
    std::vector <std::string> serverCommand = split(cmd);

    if ( serverCommand[0] == "exit" )
        return true;

    return false;
}

int main( int argc, char **argv )
{
    DDServer::Server server(550, 100);
    DDServer::Log serverLog("server.log");

    std::cout << "Starting server." << std::endl;
    server.setLog(&serverLog);
    server.startListening();

    bool done = false;
    while(!done)
    {
        std::string cmd;
        std::cout << "DDServer: ";
        std::getline(std::cin, cmd);
        

        if (!cmd.empty())
            done = processCommand(cmd);
    
    }

 
    server.stopServer();
    return 0;
}