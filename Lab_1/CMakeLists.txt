cmake_minimum_required(VERSION 3.29)
project(Lab_1)

set(CMAKE_CXX_STANDARD 23)

add_executable(Lab_1 main.cpp
        MulticastApp.cpp
        MulticastApp.hpp
        Sender.cpp
        Sender.hpp
        Receiver.cpp
        Receiver.hpp
        KnownInstancesStorage.cpp
        KnownInstancesStorage.hpp
)
