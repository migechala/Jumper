#include <iostream>
#include "Objects.h"
#include "Logger.h"
#include "Types.h"

ObjectBase::ObjectBase(type::Vector2i position, type::Vector2i size, SDL_Color color): position(position), size(size), color(color), dst({position.x, position.y, size.x, size.y}), velocity(0, 0){}

Player::Player(type::Vector2i position, type::Vector2i size, SDL_Color color): ObjectBase(position, size, color), jumpHeight(50){}

Platform::Platform(type::Vector2i position, type::Vector2i size, SDL_Color color): ObjectBase(position, size, color){}



int Player::jump(){
    if (velocity.y == 0 && dst.y >= 100){
        velocity.y = jumpHeight;
        LOG_INFO("Jumping with velocity: " + std::to_string(velocity.y));
        return 0;
    }
    LOG_ERR("Failed to jump with velocity: " + std::to_string(velocity.y));
    return -1;
}

int Player::update(){
    int ret = 0;
    return ret;
}