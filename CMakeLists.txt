cmake_minimum_required(VERSION 3.15)
project(POSIX_queues)

set(CMAKE_CXX_STANDARD 17)

include_directories(MessageQueueLib/includes)

add_subdirectory(MessageQueueLib)
add_subdirectory(server)
add_subdirectory(client)