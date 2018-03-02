#include <iostream>
#include <vector>
#include <string>
#include <sstream>

#include "Utils.hpp"
#include "Client.hpp"
#include "ClientDriver.hpp"

void showUsage()
{
    std::cout << "\nHelp\n\n\texit\t\tExits program" << std::endl;
    std::cout << "\n\tcreateClient\t\tAdd client" << std::endl;
    std::cout << "\tlist\t\tShow all clients" << std::endl;
}

int main( int argc, char **argv )
{
    ClientDriver myClientDriver;
    std::string buffer;
    if (argc != 3 )
    {
        std::cout << "Usage:\n\tccdrive [ip] [port]" << std::endl;
        return 0;
    }

    bool done = false;
    while(!done)
    {
        myClientDriver.processMessages();

        std::cout << "\nCDriver: ";
        std::getline(std::cin, buffer);

        std::vector <std::string> tokens = tokenize(buffer);

        if ( !tokens.empty() )
        {

            if (tokens[0] == "exit" || tokens[0] == "quit")
            {
                myClientDriver.broadCastMessage("shutdown");
                done = true;
            }
            if ( tokens[0] == "help")
                showUsage();

            if (tokens[0] == "createClient" || tokens[0] == "cc")
            {
                std::cout << "\tLaunching new Client!" << std::endl;
                myClientDriver.launchClient(argv[1], std::atoi(argv[2]));
            }

            if (tokens[0] == "list")
            {
                myClientDriver.showClients();
            }

            if (tokens[0] == "broadcast")
            {
                std::string completeMessage;

                for ( unsigned int c = 1; c < tokens.size(); c++ )
                {
                    completeMessage += tokens[c];
                    if (c < tokens.size()-1)
                        completeMessage+=' ';
                }
                myClientDriver.broadCastMessage(completeMessage);
            }

            if (tokens[0] == "send")
            {
                int id = std::stoi(tokens[1]);
                
                std::string completeMessage;
                for ( unsigned int c = 2; c < tokens.size(); c++ )
                {
                    completeMessage += tokens[c];
                    if (c < tokens.size()-1)
                        completeMessage+=' ';
                }

                std::cout << "\n\t\tSending to " << id << ": " << completeMessage << std::endl;
                myClientDriver.sendMessage(id, completeMessage);
            }
        }
    }

    myClientDriver.joinAll();
    std::cin.get();
    return 0;
}