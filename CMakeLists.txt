cmake_minimum_required(VERSION 3.0.0)
project(TestServer LANGUAGES CXX VERSION 0.0.0)

add_subdirectory(src)

include(CTest)
enable_testing()

find_package (Threads)
add_executable(TestServer main.cpp)
target_link_libraries(TestServer LINK_PUBLIC Src ${CMAKE_THREAD_LIBS_INIT})
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

