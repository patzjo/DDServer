set(NEEDED_FILES
    Account.cpp
    Client.cpp
    Communication.cpp
    Game.cpp
    Log.cpp
    Lobby.cpp
    Message.cpp
    Server.cpp
    ServerListener.cpp
)

add_library(Src ${NEEDED_FILES})
target_include_directories(Src PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

