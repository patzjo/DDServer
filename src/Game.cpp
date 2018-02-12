#include "Game.hpp"

#include <iostream>
#include <string>
#include <vector>
#include <unistd.h>
#include <memory>

namespace DDServer
{
    void DDGame::run()
    {
        while(1) // TODO(jonne): Loop should end with message
        {
            if ( status == WAITING )
            {
                sleep(10);
                std::string statusString;

                switch(status)
                {
                    case WAITING:
                    statusString = "Waiting...";
                    break;

                    case ACTIVE:
                    statusString = "Active...";
                    break;

                    case WAITING_USER:
                    statusString = "Waiting user...";
                    break;
                }
            }
//            std::cout << "GAME " << gameThreadID << " status: " << std::endl;
        }

    }

//    void threadRunner(int id, const DDGame& game) { game.run(); }
    void threadRunner(int id, std::shared_ptr<DDGame> game)
    {
//        std::cout << "Starting " << id << std::endl;
        game->run();
    }

}