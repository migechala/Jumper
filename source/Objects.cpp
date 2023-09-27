#include <iostream>
#include "KeyboardManager.h"
#include "Objects.h"
#include "Logger.h"
#include "Types.h"

ObjectBase::ObjectBase(type::Vector2i position, type::Vector2i size, SDL_Color color) : position(position), size(size), color(color), dst({position.x, position.y, size.x, size.y}), velocity(0, 0), rising(false) {}

Player::Player(type::Vector2i position, type::Vector2i size, SDL_Color color, int maxWidth) : ObjectBase(position, size, color), jumpHeight(25), maxWidth(maxWidth)
{
    enableControl();
}

void Player::removeControl()
{
    KeyboardManager::getInstance()->removeListener(SDL_SCANCODE_W);
    KeyboardManager::getInstance()->removeListener(SDL_SCANCODE_A);
    KeyboardManager::getInstance()->removeListener(SDL_SCANCODE_S);
    KeyboardManager::getInstance()->removeListener(SDL_SCANCODE_D);
}

void Player::enableControl()
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
    KeyboardManager::getInstance()->addListener(
        SDL_SCANCODE_SPACE, [this]()
        { up(); },
        true);
    KeyboardManager::getInstance()->addListener(
        SDL_SCANCODE_S, [this]()
        { down(); },
        true);
}

Platform::Platform(type::Vector2i position, type::Vector2i size, SDL_Color color, int speed) : ObjectBase(position, size, color) { this->velocity.x = speed; }
void Player::left()
{
    if (this->position.x - 10 >= 0)
    {
        this->position.x -= 10;
    }
    else
    {
        this->position.x = 0;
    }
}
void Player::right()
{
    if (this->position.x + 10 <= maxWidth - this->size.x)
    {
        this->position.x += 10;
    }
    else
    {
        this->position.x = maxWidth - this->size.x;
    }
}
void Player::up()
{
    jump();
}
int Player::jump()
{
    if (velocity.y == 0 && !rising)
    {
        velocity.x = 0;
        velocity.y = jumpHeight;
        position.y += 2;
        rising = true;
        return 0;
    }
    return -1;
}

void Player::down()
{
    if (position.y > 0 && !rising)
    {
        // rising = true;
        position.y -= 30;
    }
}

int Player::update()
{
    int ret = jump();
    return ret;
}