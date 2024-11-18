//
// Created by plushjill on 03.11.2024.
//

#ifndef SNAKE_GAME_PROTOBUF_MANAGER_HPP
#define SNAKE_GAME_PROTOBUF_MANAGER_HPP
#include "snakes.pb.h"
#include <boost/asio.hpp>
#include "include/entity/coord_point.hpp"
#include "include/entity/snake.hpp"
#include "include/entity/game_config.hpp"
#include "include/entity/game_state.hpp"
#include "entity/game_messages/game_message.hpp"
#include "entity/game_messages/join_message.hpp"

class ProtobufManager {
public:
    static snakes::GameState::Coord create_coord(
            CoordPoint coord_point
    );

    static snakes::GameConfig create_game_config(
            GameConfig config
    );

    static snakes::GamePlayer create_game_player(
            const GamePlayer& game_player
    );

    static snakes::GamePlayers add_game_players(
            const std::vector<snakes::GamePlayer>& players
            );

    static snakes::GameState create_game_state(
            const GameState& state
            );

    static snakes::Direction get_snakes_direction(
            Direction direction
            );

    static snakes::GameState::Snake::SnakeState get_snakes_state(
            SnakeState state
    );

    static snakes::PlayerType get_snakes_player_type(
            PlayerType type
    );

    static snakes::GamePlayers create_game_players(
            const std::vector<GamePlayer>& players
    );

    static snakes::GameMessage create_game_message(
            const GameMessage& message
            );
    static snakes::GameMessage::JoinMsg create_join_message(
            const JoinMessage& message
            );
    static snakes::NodeRole get_snakes_node_role(
            NodeRole role
            );

    static void set_message(snakes::GameMessage &snakes_game_message, const GameMessage &message);
};


#endif //SNAKE_GAME_PROTOBUF_MANAGER_HPP