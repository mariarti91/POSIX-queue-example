cmake_minimum_required(VERSION 3.15)
project(POSIX_queues)

set(CMAKE_CXX_STANDARD 17)

add_executable(client main.cpp)
target_link_libraries(client libomq)