//
// Created by plushjill on 03.11.2024.
//

#ifndef SNAKE_GAME_NODE_ROLE_HPP
#define SNAKE_GAME_NODE_ROLE_HPP

enum class NodeRole {
    Normal = 0, // Обычный узел, лист в топологии "звезда"
    Master = 1, // Главный узел, центр в топологии "звезда"
    Deputy = 2, // Заместитель главного узла
    Viewer = 3 // Наблюдатель, похож на NORMAL, но не имеет змеи в статусе ALIVE, только получает обновления статуса
};

#endif //SNAKE_GAME_NODE_ROLE_HPP
