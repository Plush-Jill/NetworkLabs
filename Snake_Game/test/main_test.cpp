//
// Created by plushjill on 18.11.2024.
//

#include <iostream>
#include "util/protobuf_manager.hpp"
#include "entities.hpp"
#include "gtest/gtest.h"
#include <format>
#include <utility>


class Base {
public:
    std::shared_ptr<int> m_number;

    explicit Base(std::shared_ptr<int> number) : m_number(std::move(number)) {};
    int get_num() {
        return *m_number;
    }
};

//int main() {
//    std::shared_ptr<int> number {std::make_shared<int>(5)};
//    Base base {number};
//    std::cout << std::format("number ptr usages count: {}", number.use_count()) << std::endl;
//    return 0;
//}
int main() {
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}