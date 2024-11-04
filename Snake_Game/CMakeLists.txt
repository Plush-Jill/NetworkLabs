cmake_minimum_required(VERSION 3.16)

project(Snake_Game VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.5 REQUIRED COMPONENTS Quick Multimedia)
find_package(Protobuf REQUIRED)

include_directories(${PROTOBUF_INCLUDE_DIRS})

qt_standard_project_setup(REQUIRES 6.5)

qt_add_executable(appSnake_Game
        src/main.cpp
        src/game_field_controller.cpp
        include/game_field_controller.hpp
        src/entity/snake.cpp
        include/entity/snake.hpp
        src/entity/snake_segment.cpp
        include/entity/snake_segment.hpp
        src/entity/coord_point.cpp
        include/entity/coord_point.hpp
        src/util/protobuf_manager.cpp
        include/util/protobuf_manager.hpp
        include/enum/snake_state.hpp
        include/enum/direction.hpp
        include/enum/player_type.hpp
        src/entity/game_player.cpp
        include/entity/game_player.hpp
        include/enum/node_role.hpp
        src/entity/game_config.cpp
        include/entity/game_config.hpp
        src/entity/game_state.cpp
        include/entity/game_state.hpp
        src/entity/game_announcement.cpp
        include/entity/game_announcement.hpp
        snakes.pb.cc
        snakes.pb.h
        src/entity/game_messages/game_message.cpp
        include/entity/game_messages/game_message.hpp
        src/entity/game_messages/abstract_message.cpp
        include/entity/game_messages/abstract_message.hpp
        include/enum/message_type.hpp
        src/entity/game_messages/ping_message.cpp
        include/entity/game_messages/ping_message.hpp
        src/entity/game_messages/steer_message.cpp
        include/entity/game_messages/steer_message.hpp
        src/entity/game_messages/ack_message.cpp
        include/entity/game_messages/ack_message.hpp
        src/entity/game_messages/state_message.cpp
        include/entity/game_messages/state_message.hpp
        src/entity/game_messages/announcement_message.cpp
        include/entity/game_messages/announcement_message.hpp
        src/entity/game_messages/discover_message.cpp
        include/entity/game_messages/discover_message.hpp
        src/entity/game_messages/join_message.cpp
        include/entity/game_messages/join_message.hpp
        src/entity/game_messages/error_message.cpp
        include/entity/game_messages/error_message.hpp
        src/entity/game_messages/role_change_message.cpp
        include/entity/game_messages/role_change_message.hpp
)

qt6_add_resources(appSnake_Game_RESOURCES resources.qrc)

qt_add_qml_module(appSnake_Game
    URI Snake_Game
    VERSION 1.0
    QML_FILES
        Main.qml
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appSnake_Game PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appSnake_Game
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appSnake_Game
    PRIVATE Qt6::Quick
        ${PROTOBUF_LIBRARIES}
#        appSnake_Game_RESOURCES
)
target_include_directories(appSnake_Game PRIVATE "./include")
include(GNUInstallDirs)
install(TARGETS appSnake_Game
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
