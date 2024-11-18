cmake_minimum_required(VERSION 3.29)
project(Lab_1)

set(CMAKE_CXX_STANDARD 23)

add_executable(Lab_1 main.cpp
        src/multicast_app.cpp
        include/multicast_app.hpp
        src/sender.cpp
        include/sender.hpp
        src/receiver.cpp
        include/receiver.hpp
        src/known_instances_storage.cpp
        include/known_instances_storage.hpp
)
