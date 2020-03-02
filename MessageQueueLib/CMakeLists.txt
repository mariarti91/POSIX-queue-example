cmake_minimum_required(VERSION 3.10)
project(POSIX_queues_client_lib VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)

add_library(libomq STATIC sources/MessageQueue.cpp includes/MessageQueue.h)
target_link_libraries(libomq rt)



set_target_properties(libomq PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(libomq PROPERTIES SOVERSION 1)

set_target_properties(libomq PROPERTIES PUBLIC_HEADER includes/MessageQueue.h)
target_include_directories(libomq PRIVATE includes)