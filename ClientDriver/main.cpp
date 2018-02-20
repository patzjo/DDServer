#include <iostream>
#include <vector>
#include <string>

#include "Client.hpp"
#include "ClientDriver.hpp"

void showUsage()
{
    std::cout << "\nHelp\n\n\texit\t\tExits program" << std::endl;
    std::cout << "\tclientAdd\t\tAdd client" << std::endl;
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
        std::cout << "\nCDriver: ";
        std::getline(std::cin, buffer);
        if (buffer == "exit")
        {
            myClientDriver.broadCastMessage("shutdown");
            done = true;
        }
        if ( buffer == "help")
            showUsage();

        if (buffer == "addClient")
        {
            std::cout << "" << std::endl;
            myClientDriver.launchClient("localhost", 5550);
        }
    }

    myClientDriver.joinAll();

    return 0;
}