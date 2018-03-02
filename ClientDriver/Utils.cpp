#include "Utils.hpp"

std::vector <std::string> tokenize(std::string buffer)
{
    std::vector <std::string> result;
    std::stringstream ss;
      std::string buf;

    ss << buffer;

    while(std::getline(ss, buf, ' '))
        result.push_back(buf);

    return result;
}