#include "gtest/gtest.h"
#include "util/protobuf_manager.hpp"


TEST(ProtobufManagerTests, create_game_player_proto) {
    GamePlayer game_player {};

    snakes::GamePlayer game_player_proto =
            ProtobufManager::create_game_player_proto(game_player);

    std::string serialized_data;
    EXPECT_TRUE(game_player_proto.SerializeToString(&serialized_data));

    snakes::GamePlayer game_player_proto_deserialized;
    EXPECT_TRUE(game_player_proto_deserialized.ParseFromString(serialized_data));

    GamePlayer game_player_from_proto {game_player_proto_deserialized};
    EXPECT_TRUE(game_player_from_proto == game_player);

    std::string deserialized_data;
    game_player_proto_deserialized.SerializeToString(&deserialized_data);
    EXPECT_TRUE(deserialized_data == serialized_data);
}

TEST(ProtobufManagerTests, create_game_config_proto) {
    std::string serialized_data;
    GameConfig game_config {};
    snakes::GameConfig game_config_proto = ProtobufManager::create_game_config_proto(
            game_config
    );

    EXPECT_TRUE(game_config_proto.SerializeToString(&serialized_data));

    snakes::GameConfig game_config_proto_deserialized;
    EXPECT_TRUE(game_config_proto_deserialized.ParseFromString(serialized_data));

    GameConfig game_config_from_proto {game_config_proto_deserialized};

    EXPECT_TRUE(game_config == game_config_from_proto);

    std::string deserialized_data;
    game_config_proto_deserialized.SerializeToString(&deserialized_data);
    EXPECT_TRUE(deserialized_data == serialized_data);
}

TEST(ProtobufManagerTests, create_game_state_proto) {
    std::string serialized_data;
    GamePlayer game_player {};

    snakes::GamePlayer game_player_proto =
            ProtobufManager::create_game_player_proto(game_player);
    Coord point1 (1, 2);
    Coord point2 (1, 3);
    Coord point3 (1, 4);
    std::shared_ptr<std::deque<Coord>> snake_segments {std::make_shared<std::deque<Coord>>()};
    snake_segments->push_back(point1);
    snake_segments->push_back(point2);
    std::vector<Coord> foods {point2, point3};
    std::vector<GamePlayer> players {game_player};

    Snake snake (0,
                 snake_segments,
                 SnakeState::Alive,
                 Direction::Up);

    std::vector<Snake> snakes {snake};

    GameState game_state (0,
                          std::make_shared<std::vector<Snake>>(snakes),
                          std::make_shared<std::vector<Coord>>(foods),
                          std::make_shared<std::vector<GamePlayer>>(players));
    snakes::GameState game_state_proto = ProtobufManager::create_game_state_proto(
            game_state
    );

    EXPECT_TRUE(game_state_proto.SerializeToString(&serialized_data));

    snakes::GameConfig game_state_proto_deserialized;
    EXPECT_TRUE(game_state_proto_deserialized.ParseFromString(serialized_data));

    std::string deserialized_data;
    game_state_proto_deserialized.SerializeToString(&deserialized_data);
    EXPECT_TRUE(deserialized_data == serialized_data);
}


TEST(ProtobufManagerTests, create_announcement_proto) {
    std::string serialized_data;
    GameAnnouncement game_announcement;
    snakes::GameAnnouncement game_announcement_proto =
            ProtobufManager::create_announcement_proto(game_announcement);

    EXPECT_TRUE(game_announcement_proto.SerializeToString(&serialized_data));


    snakes::GameAnnouncement game_announcement_proto_deserialized;
    EXPECT_TRUE(game_announcement_proto_deserialized.ParseFromString(serialized_data));

    std::string deserialized_data;
    EXPECT_TRUE(game_announcement_proto_deserialized.SerializeToString(&deserialized_data));
    EXPECT_TRUE(deserialized_data == serialized_data);
}