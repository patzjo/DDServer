#pragma once
#include <string>
#include <vector>
#include <memory>

namespace DDServer
{
#define MAX_CARDS 25

enum ETURN {PLAYER1,PLAYER2};
enum ESERVER_STATUS {WAITING, ACTIVE, WAITING_USER};

    struct GameOptions
    {
        float turnTime;
    };

    struct Card
    {
        int card;
    };

    class Player
    {
    public:
        
    private:
        std::string name;
        Card deck[25];
        std::vector <Card> hand;
        float timer = 0.0f;
    };

    class DDGame
    {
    public:
        DDGame(int id) { gameThreadID = id; }

        void run();

    private:
        int gameThreadID;
        Player players[2];
        ETURN turn;
        GameOptions options;
        bool waiting = true;

        ESERVER_STATUS status;
    };

//    void threadRunner(int id, const DDGame& game);
    void threadRunner(int id, std::shared_ptr <DDGame> game);

}