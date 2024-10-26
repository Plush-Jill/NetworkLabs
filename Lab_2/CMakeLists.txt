cmake_minimum_required(VERSION 3.29)
project(Lab_2)

set(CMAKE_CXX_STANDARD 26)

# Первая сборка
add_executable(client _client/main_client.cpp)

target_link_libraries(client
        boost_filesystem
        boost_iostreams
)

# Вторая сборка
add_executable(server _server/main_server.cpp
        _server/Server.cpp
        _server/Server.hpp
        _server/ClientInfo.cpp
        _server/ClientInfo.hpp)

# Добавляем ключи для компиляции сервера
target_link_libraries(server
        boost_filesystem
        boost_system
        boost_timer
)
