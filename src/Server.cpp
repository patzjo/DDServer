#include "Server.hpp"
#include "Log.hpp"

namespace DDServer
{
    Server::Server(int portnum, int ThreadCount)
    { 
        listener.setPort(portnum);
        threadCount = ThreadCount+1; // ThreadCount + listener

        threads.resize(threadCount); 
        }

    bool Server::startListening()
    {
        listener.setLog(log);
        listener.setThreads(&threads);
        log->push("TRYING: Starting games in threads");
        startServer();

        threads.push([&](int id){ listener.start(); });
        //threads.push(listener.start); // should set this as own thread
    }

    void Server::stopServer()
    {
        exit(1);
        std::terminate(); // Tape patent till proper messaging system is implemented.
    }

    void Server::startServer()
    {
        for(unsigned int c = 0; c < threadCount-1; c++)
        {
            std::cout << "Launching game: " << c+1 << std::endl;
            std::shared_ptr <DDGame> game = std::make_shared<DDGame>(c+1);
            games.emplace_back(game);
            threads.push(threadRunner, game);

        }
    }

}
