//
// Created by plushjill on 18.11.2024.
//

#include <iostream>
#include "util/protobuf_manager.hpp"
#include "entities.hpp"


int main() {

    GamePlayer game_player {};


    snakes::GamePlayer game_player_proto =
            ProtobufManager::create_game_player_proto(game_player);


    std::string serialized_data;
    if (game_player_proto.SerializeToString(&serialized_data)) {
    } else {
        std::cerr << "Serializing error" << std::endl;
    }
    snakes::GamePlayer game_player_proto_deserialized;
    if (game_player_proto_deserialized.ParseFromString(serialized_data)) {
        std::string deserialized_data;
        game_player_proto_deserialized.SerializeToString(&deserialized_data);
        if (deserialized_data == serialized_data) {
            std::cout << "Test passed (GamePlayer)" << std::endl;
        }
    } else {
        std::cerr << "Deserialization error" << std::endl;
    }





    GameConfig game_config {};
    snakes::GameConfig game_config_proto = ProtobufManager::create_game_config_proto(
            game_config
    );

    if (game_config_proto.SerializeToString(&serialized_data)) {
    } else {
        std::cerr << "Serializing error" << std::endl;
    }
    snakes::GameConfig game_config_proto_deserialized;
    if (game_config_proto_deserialized.ParseFromString(serialized_data)) {
        std::string deserialized_data;
        game_config_proto_deserialized.SerializeToString(&deserialized_data);
        if (deserialized_data == serialized_data) {
            std::cout << "Test passed (GameConfig)" << std::endl;
        }
    } else {
        std::cerr << "Deserialization error" << std::endl;
    }




    CoordPoint point1 (1, 2);
    CoordPoint point2 (1, 3);
    CoordPoint point3 (1, 4);
    std::vector<CoordPoint> snake_segments {point1, point2};
    std::vector<CoordPoint> foods {point2, point3};
    std::vector<GamePlayer> players {game_player};

    Snake snake (0,
                 snake_segments,
                 SnakeState::Alive,
                 Direction::Up);

    std::vector<Snake> snakes {snake};

    GameState game_state (0, snakes, foods, players);
    snakes::GameState game_state_proto = ProtobufManager::create_game_state_proto(
            game_state
    );

    if (game_state_proto.SerializeToString(&serialized_data)) {
    } else {
        std::cerr << "Serializing error" << std::endl;
    }
    snakes::GameConfig game_state_proto_deserialized;
    if (game_state_proto_deserialized.ParseFromString(serialized_data)) {
        std::string deserialized_data;
        game_state_proto_deserialized.SerializeToString(&deserialized_data);
        if (deserialized_data == serialized_data) {
            std::cout << "Test passed (GameState)" << std::endl;
        }
    } else {
        std::cerr << "Deserialization error" << std::endl;
    }
}