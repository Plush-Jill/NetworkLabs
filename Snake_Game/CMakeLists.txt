cmake_minimum_required(VERSION 3.16)
project(Snake_Game VERSION 0.1 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 23)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 6.8 REQUIRED COMPONENTS Core Gui Qml Quick Qml)
find_package(Protobuf REQUIRED)
find_package(OpenGL REQUIRED)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(PROTOBUF_GENERATED_SRC_DIR "${CMAKE_SOURCE_DIR}/src")
set(PROTOBUF_GENERATED_HDR_DIR "${CMAKE_SOURCE_DIR}/include")
protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS snakes.proto)
include_directories(${PROTOBUF_INCLUDE_DIRS})


qt_standard_project_setup(REQUIRES 6.8)

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
        include/main_window_controller.hpp
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
        src/model/game_field.cpp
        include/model/game_field.hpp
        include/exceptions/incomplete_code_exception.hpp
        include/exceptions_all.hpp
        src/controller/snake_controller.cpp
        include/controller/snake_controller.hpp
        src/model/game_model.cpp
        include/model/game_model.hpp
        include/grid_model.cpp
        include/grid_model.hpp
        include/util/in_game_config.cpp
        include/util/in_game_config.hpp
)

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
        boost_filesystem
)


target_include_directories(appSnake_Game PRIVATE "./include")
include(GNUInstallDirs)
install(TARGETS appSnake_Game
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)



add_executable(test_target

        test/main_test.cpp

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
        test/protobuf_manager_test.cpp
        src/model/game_field.cpp
        include/model/game_field.hpp
        include/exceptions/incomplete_code_exception.hpp
        include/exceptions_all.hpp
        test/coord_point_test.cpp
)

if(POLICY CMP0135)
    cmake_policy(SET CMP0135 NEW)
    set(CMAKE_POLICY_DEFAULT_CMP0135 NEW)
endif()

include(FetchContent)
FetchContent_Declare(
        googletest
        # Specify the commit you depend on and update it regularly.
        URL https://github.com/google/googletest/archive/58d77fa8070e8cec2dc1ed015d66b454c8d78850.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

target_link_libraries(test_target PRIVATE
        ${PROTOBUF_LIBRARIES}
        protobuf::libprotobuf
        boost_filesystem
        gtest_main
)

install(TARGETS test_target
        BUNDLE DESTINATION .
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

target_include_directories(test_target PRIVATE "./include")
