//
// Created by plushjill on 18.11.2024.
//

#include <iostream>
#include "util/protobuf_manager.hpp"
#include "entities.hpp"
#include "gtest/gtest.h"
#include <format>

int main() {

    std::cout << std::format("{} {}", (-6) % 4, 6 % 4) << std::endl;
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}