cmake_minimum_required(VERSION 3.15)
project(POSIX_queues)

set(CMAKE_CXX_STANDARD 17)

add_executable(server main.cpp)
target_link_libraries(server libomq)