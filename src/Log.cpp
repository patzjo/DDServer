#include <iostream>
#include <fstream>
#include <chrono>
#include <ctime>

#include "Log.hpp"

namespace DDServer
{
    Log::Log( std::string logFilename )
    {
        filename = logFilename;
        logFile.open(filename, std::fstream::out | std::fstream::app);
    }

    Log::~Log()
    {
        write();
        if ( logFile.is_open() )
            logFile.close();
    }

    void Log::push(std::string logLine)
    {
        std::lock_guard<std::mutex> lock(logMutex);
        char buf[80];
        struct tm *timeinfo;
        time_t rawTime;


        time(&rawTime);
        timeinfo = localtime(&rawTime);
        strftime(buf, 80, "%d.%m.%Y %X", timeinfo);
        
        std::string timeString = buf;

        std::string completeLogLine = timeString + " > " + logLine;
        
        std::cout << completeLogLine << std::endl;

        buffer.push_back(completeLogLine);
        if ( buffer.size() >= 1) // Todo(Jonne): Change this to bigger number after test cases.
            write();

    }

    void Log::write()
    {
//        std::lock_guard<std::mutex> lock(logMutex);

        if (!logFile.is_open())
        {
            std::cerr << "Can't write to logfile!" << std::endl;
            return;
        }

        for ( auto& line : buffer )
            logFile << line << std::endl;

        buffer.clear();
    }

}