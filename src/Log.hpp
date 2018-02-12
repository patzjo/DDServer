#pragma once

#include <fstream>
#include <string>
#include <vector>
#include <mutex>

namespace DDServer
{
    // Todo(Jonne): Really should use better initializion to filename.
    //              Another todo should be variable that determines how many
    //              lines will be written at once
    class Log
    {
        public:
        
        Log(std::string logFilename = "defaultlogname.log");
        ~Log();

        void push(std::string logLine);
        void write();

        private:
        std::vector <std::string> buffer;
        std::string filename;
        std::fstream logFile;

        std::mutex logMutex;
    };
}