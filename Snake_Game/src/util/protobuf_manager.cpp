//
// Created by plushjill on 03.11.2024.
//

#include "include/util/protobuf_manager.hpp"
#include "entity/game_messages/steer_message.hpp"
#include "entity/game_messages/ack_message.hpp"
#include "entity/game_messages/state_message.hpp"
#include "entity/game_messages/announcement_message.hpp"
#include "entity/game_messages/error_message.hpp"
#include "entity/game_messages/role_change_message.hpp"
#include "entity/game_messages/discover_message.hpp"


snakes::GamePlayers ProtobufManager::add_game_players(
        const std::vector<snakes::GamePlayer> &players) {
    snakes::GamePlayers game_players;
    for (const auto& player : players) {
        *game_players.add_players() = player;
    }

    return game_players;
}

snakes::GameConfig ProtobufManager::create_game_config(
        GameConfig config
) {
    snakes::GameConfig game_config;
    game_config.set_width(config.get_field_width());
    game_config.set_height(config.get_field_height());
    game_config.set_food_static(config.get_food_static());
    game_config.set_state_delay_ms(config.get_state_delay_ms().count());

    return game_config;
}

snakes::GameState ProtobufManager::create_game_state(
        const GameState& state
) {
    snakes::GameState game_state;
    game_state.set_state_order(state.get_state_order());


    for (const Snake& snake : state.get_snakes()) {
        snakes::GameState::Snake* new_snake = game_state.add_snakes();

        new_snake->set_player_id(snake.get_id());

        *new_snake->add_points() = ProtobufManager::create_coord(
                snake.get_head().get_coord_point());
        CoordPoint previous_point = snake.get_head().get_coord_point();

        for (SnakeSegment segment : snake.get_segments()) {
            CoordPoint next_point = segment.get_coord_point();
            *new_snake->add_points() = ProtobufManager::create_coord(
                    next_point.get_shift_from(previous_point));

            previous_point = next_point;
        }

        new_snake->set_state(ProtobufManager::get_snakes_state(snake.get_snake_state()));

        new_snake->set_head_direction(
                ProtobufManager::get_snakes_direction(
                        snake.get_head_direction()));
    }

    for (const CoordPoint& food : state.get_foods()) {
        *game_state.add_foods() = ProtobufManager::create_coord(food);
    }

    return game_state;

}

snakes::GameState::Coord ProtobufManager::create_coord(
        CoordPoint coord_point
) {
    snakes::GameState::Coord coord;
    coord.set_x(coord_point.get_x());
    coord.set_y(coord_point.get_y());
    return coord;
}

snakes::GamePlayers ProtobufManager::create_game_players(
        const std::vector<GamePlayer>& players) {

    snakes::GamePlayers game_players;
    for (const GamePlayer& game_player : players) {
        *game_players.add_players() = ProtobufManager::create_game_player(game_player);
    }

    return game_players;
}

snakes::GamePlayer ProtobufManager::create_game_player(
        const GamePlayer &game_player
) {

    snakes::GamePlayer player;
    player.set_name(game_player.get_name());
    player.set_id(game_player.get_id());
    player.set_ip_address(game_player.get_ip_address().to_string());
    player.set_port(game_player.get_port());
    player.set_type(ProtobufManager::get_snakes_player_type(game_player.get_type()));
    player.set_score(game_player.get_score());

    return player;
}

snakes::PlayerType ProtobufManager::get_snakes_player_type(
        PlayerType type
) {
    switch (type) {

        case PlayerType::Human: return snakes::PlayerType::HUMAN;
            break;
        case PlayerType::Robot: return snakes::PlayerType::ROBOT;
            break;
        default: throw std::exception();
    }
}

snakes::GameState::Snake::SnakeState ProtobufManager::get_snakes_state(
        SnakeState state
) {
    switch (state) {
        case SnakeState::Alive: return snakes::GameState_Snake_SnakeState_ALIVE;
            break;
        case SnakeState::Zombie: return snakes::GameState_Snake_SnakeState_ZOMBIE;
            break;
        default: throw std::exception();
    }
}

snakes::Direction ProtobufManager::get_snakes_direction(
        Direction direction
) {
    switch (direction) {
        case Direction::Up: return snakes::Direction::UP;
            break;
        case Direction::Down: return snakes::Direction::DOWN;
            break;
        case Direction::Left: return snakes::Direction::LEFT;
            break;
        case Direction::Right: return snakes::Direction::RIGHT;
            break;
        default: throw std::exception();
    }
}

snakes::GameMessage ProtobufManager::create_game_message(
        const GameMessage& message
) {
    snakes::GameMessage game_message;

    game_message.set_msg_seq(message.get_msg_seq());
    game_message.set_sender_id(message.get_sender_id());
    game_message.set_receiver_id(message.get_receiver_id());
    set_message(game_message, message);

    return game_message;
}

void ProtobufManager::set_message(snakes::GameMessage &snakes_game_message, const GameMessage &message) {
    AbstractMessage* abstract_message = message.get_message().get();

    switch (message.get_message()->get_message_type()) {

        case MessageType::PingMsg: {
            auto* ping_msg = new snakes::GameMessage::PingMsg;
            snakes_game_message.set_allocated_ping(ping_msg);
            break;
        }
        case MessageType::SteerMsg: {
            auto* steer_message = dynamic_cast<SteerMessage*>(
                    abstract_message
            );
            if (steer_message) {
                auto* steer_msg = new snakes::GameMessage::SteerMsg;
                steer_msg->set_direction(
                        get_snakes_direction(
                                steer_message->get_direction())
                                );
                snakes_game_message.set_allocated_steer(steer_msg);
            } else {
                throw std::runtime_error("can't cast abstract_message to SteerMessage");
            }
            break;
        }
        case MessageType::AckMsg: {
            auto* ack_message = dynamic_cast<AckMessage*>(
                    abstract_message
                    );
            if (ack_message) {
                auto* ack_msg = new snakes::GameMessage::AckMsg;
                snakes_game_message.set_allocated_ack(ack_msg);
            } else {
                throw std::runtime_error("can't cast abstract_message to AckMessage");
            }
            break;
        }

        case MessageType::StateMsg: {
            auto* state_message = dynamic_cast<StateMessage*>(
                    abstract_message
                    );
            if (state_message) {
                auto* allocated_state_msg = new snakes::GameMessage::StateMsg;
                auto* allocated_game_state = new snakes::GameState;
                allocated_game_state->CopyFrom(
                        create_game_state(
                                state_message->get_game_state())
                        );
                allocated_state_msg->set_allocated_state(allocated_game_state);
                snakes_game_message.set_allocated_state(allocated_state_msg);
            } else {
                throw std::runtime_error("can't cast abstract_message to StateMessage");
            }
            break;
        }
        case MessageType::AnnouncementMsg: {
            auto* announcement_message = dynamic_cast<AnnouncementMessage*>(
                    abstract_message
            );

            if (announcement_message) {
                auto* allocated_announcement_msg =
                        new snakes::GameMessage::AnnouncementMsg;

            } else {
                throw std::runtime_error("can't cast abstract_message to AnnouncementMessage");
            }
            break;
        }
        case MessageType::JoinMsg: {
            auto* join_message = dynamic_cast<JoinMessage*>(
                    abstract_message
                    );

            if (join_message) {
                auto *allocated_join_msg =
                        new snakes::GameMessage::JoinMsg;
                allocated_join_msg->CopyFrom(
                        create_join_message(*join_message)
                        );
                snakes_game_message.set_allocated_join(allocated_join_msg);
            } else {
                throw std::runtime_error("can't cast abstract_message to JoinMessage");
            }
            break;
        }
        case MessageType::ErrorMsg: {
            auto* error_message = dynamic_cast<ErrorMessage*>(
                    abstract_message
                    );
            if (error_message) {
                auto* allocated_error_msg = new snakes::GameMessage::ErrorMsg;
                allocated_error_msg->set_error_message(error_message->get_error_message());
                snakes_game_message.set_allocated_error(allocated_error_msg);
            } else {
                throw std::runtime_error("can't cast abstract_message to ErrorMessage");
            }
            break;
        }
        case MessageType::RoleChangeMsg: {
            auto* role_changing_message = dynamic_cast<RoleChangeMessage*>(
                    abstract_message
                    );

            if (role_changing_message) {
                auto *allocated_role_change_msg = new snakes::GameMessage::RoleChangeMsg;
                allocated_role_change_msg->set_receiver_role(
                        get_snakes_node_role(
                                role_changing_message->get_receiver_role())
                        );
                allocated_role_change_msg->set_sender_role(
                        get_snakes_node_role(
                                role_changing_message->get_sender_role())
                );
                snakes_game_message.set_allocated_role_change(allocated_role_change_msg);

            } else {
                throw std::runtime_error("can't cast abstract_message to RoleChangeMessage");
            }
            break;
        }
        case MessageType::DiscoverMsg: {
            auto* discover_message = dynamic_cast<DiscoverMessage*>(
                    abstract_message
            );
            if (discover_message) {
                auto* discover_msg = new snakes::GameMessage::DiscoverMsg;
                snakes_game_message.set_allocated_discover(discover_msg);
            } else {
                throw std::runtime_error("can't cast abstract_message to DiscoverMessage");
            }
            break;
        }
    }
}

snakes::GameMessage::JoinMsg ProtobufManager::create_join_message(const JoinMessage &message) {
    snakes::GameMessage::JoinMsg join_msg;
    join_msg.set_player_type(
            ProtobufManager::get_snakes_player_type(message.get_player_type())
            );
    join_msg.set_player_name(message.get_player_name());
    join_msg.set_game_name(message.get_game_name());
    join_msg.set_requested_role(
            ProtobufManager::get_snakes_node_role(message.get_node_role())
            );

    return join_msg;
}

snakes::NodeRole ProtobufManager::get_snakes_node_role(NodeRole role) {
    switch (role) {

        case NodeRole::Normal: return snakes::NodeRole::NORMAL;
            break;
        case NodeRole::Master: return snakes::NodeRole::MASTER;
            break;
        case NodeRole::Deputy: return snakes::NodeRole::DEPUTY;
            break;
        case NodeRole::Viewer: return snakes::NodeRole::VIEWER;
            break;
        default: throw std::exception();
    }
}
