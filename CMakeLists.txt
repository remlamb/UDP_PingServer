cmake_minimum_required (VERSION 3.18)
project(Echo)

set (CMAKE_CXX_STANDARD 20)
set (CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SFML COMPONENTS system network CONFIG REQUIRED)

add_executable(client client.cpp)
add_executable(server server.cpp)

target_link_libraries(client PRIVATE sfml-system sfml-network)
target_link_libraries(server PRIVATE sfml-system sfml-network)
