#include "game_mediator.h"
#include "entities/snake.h"
#include "entities/food.h"

bool gm::eat_food(sn::snake& snake, const sn::food& food) {
    return snake.eat(food.get_food());
}

