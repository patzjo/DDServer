set(NEEDED_FILES
    ServerListener.cpp
    Client.cpp
    Server.cpp
    Message.cpp
    Log.cpp
    Game.cpp
)

add_library(Src ${NEEDED_FILES})
target_include_directories(Src PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

