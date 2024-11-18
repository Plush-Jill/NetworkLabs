cmake_minimum_required(VERSION 3.16)


#-DCMAKE_CXX_COMPILER=/usr/bin/g++
#-DQT_QMAKE_EXECUTABLE=/home/plushjill/Qt/6.8.0/gcc_64/bin/qmake
#-DCMAKE_GENERATOR=Ninja
#-DCMAKE_PREFIX_PATH=/home/plushjill/Qt/6.8.0/gcc_64
#-DCMAKE_BUILD_TYPE=Debug
#-DCMAKE_PROJECT_INCLUDE_BEFORE=build/Desktop_Qt_6_8_0-Debug/.qtc/package-manager/auto-setup.cmake
#-DCMAKE_C_COMPILER=/usr/bin/gcc
project(Snake_Game VERSION 0.1 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 23)

# Указываем компиляторы
set(CMAKE_CXX_COMPILER "/usr/bin/g++")
set(CMAKE_C_COMPILER "/usr/bin/gcc")

# Путь к qmake и Qt
set(QT_QMAKE_EXECUTABLE "/home/plushjill/Qt/6.8.0/gcc_64/bin/qmake")
set(CMAKE_PREFIX_PATH "/home/plushjill/Qt/6.8.0/gcc_64")

# Используем генератор Ninja
set(CMAKE_GENERATOR "Ninja")

# Указываем тип сборки
set(CMAKE_BUILD_TYPE "Debug")

# Указываем путь к автоконфигурации
set(CMAKE_PROJECT_INCLUDE_BEFORE "${CMAKE_BINARY_DIR}/Desktop_Qt_6_8_0-Debug/.qtc/package-manager/auto-setup.cmake")



set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


set(CMAKE_CXX_STANDARD 23)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(PROTOBUF_GENERATED_SRC_DIR "${CMAKE_SOURCE_DIR}/src")
set(PROTOBUF_GENERATED_HDR_DIR "${CMAKE_SOURCE_DIR}/include")

find_package(Qt6 6.8 REQUIRED COMPONENTS Core Gui Qml Quick Qml)
find_package(Protobuf REQUIRED)
find_package(OpenGL REQUIRED)

protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS snakes.proto)

include_directories(${PROTOBUF_INCLUDE_DIRS})

qt_standard_project_setup(REQUIRES 6.8)

qt_add_executable(appSnake_Game
        src/main.cpp
        src/game_field_controller.cpp
        appSnake_Game_resources.qrc
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

        ${PROTO_SRCS}
        ${PROTO_HDRS}

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
        resources/Snake_Game_Window/Snake_Game_WindowContent/App.qml
        src/main_window_controller.cpp
        src/main_window_controller.hpp
        src/util/config_editor.cpp
        include/util/config_editor.hpp
        src/game_model.cpp
        include/game_model.hpp
        src/announcement_sender.cpp
        include/announcement_sender.hpp

        include/entities.hpp
        include/entity/game_messages.hpp
        include/enums.hpp
        include/utils.hpp
)

qt6_add_resources(RESOURCES appSnake_Game_resources.qrc)

set_target_properties(appSnake_Game PROPERTIES
        QT_QML_URI "org.example.appSnake_Game"
)
#qt6_add_resources(qrc_srcs ${CMAKE_CURRENT_SOURCE_DIR}/appSnake_Game_resources.qrc)

set_source_files_properties(
        "./resources/Snake_Game_Window/Snake_Game_WindowContent/App.qml"
        PROPERTIES QT_RESOURCE_ALIAS App.qml
)

add_library(qrc STATIC ${qrc_srcs})

qt_add_qml_module(appSnake_Game
    URI Snake_Game
    VERSION 1.0
    QML_FILES
        resources/Snake_Game_Window/Snake_Game_WindowContent/MainMenu.qml
)
set_source_files_properties(
        "./resources/Snake_Game_Window/Snake_Game_WindowContent/MainMenu.qml"
        PROPERTIES QT_RESOURCE_ALIAS MainMenu.qml
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

#add_library(appSnake_Game_resources SHARED ${SNAKE_GAME_RESOURCES})

target_link_libraries(appSnake_Game PRIVATE
        Qt6::Quick
        ${PROTOBUF_LIBRARIES}
        Qt6::Quick
        Qt6::Qml
        Qt6::Network
        Qt6::OpenGL
        Qt6::Gui
        Qt6::Core
        protobuf::libprotobuf
        OpenGL::GL
        qrc
        boost_filesystem
#        ${SNAKE_GAME_RESOURCES}
#        appSnake_Game_resources

)
target_include_directories(appSnake_Game PRIVATE "./include")
include(GNUInstallDirs)
install(TARGETS appSnake_Game
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)



add_executable(test_target

        main_test.cpp

        ${PROTO_SRCS}
        ${PROTO_HDRS}

        include/entities.hpp
        include/entity/game_messages.hpp
        include/util/protobuf_manager.hpp
        include/enums.hpp

        src/entity/snake.cpp
        include/entity/snake.hpp
        src/entity/snake_segment.cpp
        include/entity/snake_segment.hpp

        src/entity/coord_point.cpp
        src/util/protobuf_manager.cpp
        src/entity/game_player.cpp
        src/entity/game_config.cpp
        src/entity/game_state.cpp
        src/entity/game_announcement.cpp
        src/entity/game_messages/game_message.cpp
        src/entity/game_messages/abstract_message.cpp
        src/entity/game_messages/ping_message.cpp
        src/entity/game_messages/steer_message.cpp
        src/entity/game_messages/ack_message.cpp
        src/entity/game_messages/state_message.cpp
        src/entity/game_messages/announcement_message.cpp
        src/entity/game_messages/discover_message.cpp
        src/entity/game_messages/join_message.cpp
        src/entity/game_messages/error_message.cpp
        src/entity/game_messages/role_change_message.cpp
)

target_link_libraries(test_target PRIVATE
        ${PROTOBUF_LIBRARIES}
        protobuf::libprotobuf
        boost_filesystem
)

install(TARGETS test_target
        BUNDLE DESTINATION .
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

target_include_directories(test_target PRIVATE "./include")
