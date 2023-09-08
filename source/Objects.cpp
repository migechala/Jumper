#include <iostream>
#include "KeyboardManager.h"
#include "Objects.h"
#include "Logger.h"
#include "Types.h"

ObjectBase::ObjectBase(type::Vector2i position, type::Vector2i size, SDL_Color color) : position(position), size(size), color(color), dst({position.x, position.y, size.x, size.y}), velocity(0, 0), rising(false) {}

Player::Player(type::Vector2i position, type::Vector2i size, SDL_Color color) : ObjectBase(position, size, color), jumpHeight(50)
{
    KeyboardManager::getInstance()->addListener(
        SDL_SCANCODE_A, [this]()
        { left(); },
        false);
    KeyboardManager::getInstance()->addListener(
        SDL_SCANCODE_D, [this]()
        { right(); },
        false);
    KeyboardManager::getInstance()->addListener(
        SDL_SCANCODE_W, [this]()
        { up(); },
        true);
}

Platform::Platform(type::Vector2i position, type::Vector2i size, SDL_Color color) : ObjectBase(position, size, color) {}
void Player::left()
{
    this->position.x -= 10;
}
void Player::right()
{
    this->position.x += 10;
}
void Player::up()
{
    jump();
}
int Player::jump()
{
    if (velocity.y == 0 && !rising)
    {
        velocity.y = jumpHeight;
        rising = true;
        return 0;
    }
    return -1;
}

int Player::update()
{
    int ret = 0;
    return ret;
}