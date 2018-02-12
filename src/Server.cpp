#include "Server.hpp"
#include "Log.hpp"

namespace DDServer
{
    bool Server::startListening()
    {
        listener.setLog(log);
        listener.setThreads(&threads);
        log->push("TRYING: Starting games in threads");
        startServer();
        listener.start(); // should set this as own thread
    }

    void Server::startServer()
    {
        int numero = 5;
        for(unsigned int c = 0; c < threadCount; c++)
        {
            std::cout << "Launching game: " << c+1 << std::endl;
            std::shared_ptr <DDGame> game = std::make_shared<DDGame>(c+1);
            games.emplace_back(game);
            threads.push(threadRunner, game);

        }
    }

}
