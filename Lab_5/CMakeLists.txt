cmake_minimum_required(VERSION 3.29)
project(Lab_5)

set(CMAKE_CXX_STANDARD 26)

add_executable(Lab_5
        main.cpp
        connection_pool.hpp
        connection.hpp
        proxy_server.hpp
        proxy_const.hpp
        proxy_server.cpp
        connection_pool.cpp
        connection.cpp
)
