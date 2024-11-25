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
#include "entity/game_announcement.hpp"

class ProtobufManager {
public:
    static snakes::GameAnnouncement create_announcement_proto(
            const GameAnnouncement &announcement
            );

    static snakes::GameState::Coord create_coord_proto(
            CoordPoint coord_point
            );

    /**
     * @tested true
     */
    static snakes::GameConfig create_game_config_proto(
            const GameConfig& config
            );

    /**
     * @tested true
     */
    static snakes::GamePlayer create_game_player_proto(
            const GamePlayer& game_player
            );

    static snakes::GamePlayers add_game_players_proto(
            const std::vector<snakes::GamePlayer>& players
            );

    static snakes::GamePlayers create_game_players_array_proto(
            const std::vector<GamePlayer>& players
    );

    /**
    * @tested true
    */
    static snakes::GameState create_game_state_proto(
            const GameState& state
            );

    static snakes::Direction get_snakes_direction_proto(
            Direction direction
            );

    static snakes::GameState::Snake::SnakeState get_snakes_state_proto(
            SnakeState state
    );

    static snakes::PlayerType get_snakes_player_type_proto(
            PlayerType type
    );

    static snakes::GamePlayers create_game_players_proto(
            const std::vector<GamePlayer>& players
    );

    static snakes::GameMessage create_game_message_proto(
            const GameMessage& message
            );
    static snakes::GameMessage::JoinMsg create_join_message_proto(
            const JoinMessage& message
            );
    static snakes::NodeRole get_snakes_node_role_proto(
            NodeRole role
            );

    static NodeRole get_node_role(
            snakes::NodeRole node_role_proto
            );

    static PlayerType get_type(
            snakes::PlayerType player_type_proto
    );
    static void set_message(snakes::GameMessage &snakes_game_message, const GameMessage &message);
};


#endif //SNAKE_GAME_PROTOBUF_MANAGER_HPP
