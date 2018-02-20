cmake_minimum_required(VERSION 3.0.0)
project(ClientDriver LANGUAGES CXX VERSION 0.0.0)

include(CTest)
enable_testing()

find_package (Threads)
add_executable(cdriver main.cpp ClientDriver.cpp Client.cpp)
target_link_libraries(cdriver LINK_PUBLIC ${CMAKE_THREAD_LIBS_INIT})
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

