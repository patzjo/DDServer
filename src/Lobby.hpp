#pragma once
#include <queue>
#include "Client.hpp"

namespace DDServer
{
    class Lobby
    {
    public:

    private:
        std::queue <Client> clients;    // Client information of all players
        int playersCount = 0;           // Players in Lobby
    };
}