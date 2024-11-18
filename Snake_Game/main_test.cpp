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
            std::cout << "Test passed" << std::endl;
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
            std::cout << "Test passed" << std::endl;
        }
    } else {
        std::cerr << "Deserialization error" << std::endl;
    }




    GameState game_state {};
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
            std::cout << "Test passed" << std::endl;
        }
    } else {
        std::cerr << "Deserialization error" << std::endl;
    }
}