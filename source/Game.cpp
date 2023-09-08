#include "Game.h"
#include "Objects.h"
#include "Logger.h"
#include <cmath>

Game::Game(WindowManager *window, Player *player) : window(window), player(player)
{
}

type::Vector2i Game::getRelativePositionFromObject(ObjectBase *object)
{
    return window->getSize() - (object->position + object->size);
}

void Game::setRelativePositionFromObject(ObjectBase *object, type::Vector2i newPos)
{
    object->position = window->getSize() - (newPos + object->size);
    object->position.x = newPos.x;
}

int Game::updateGravity(ObjectBase *object)
{
    if (getRelativePositionFromObject(object).y >= 0)
    {
        velModifier += -0.1;
        object->velocity.y += velModifier;
        object->position.y -= object->velocity.y;
    }
    else
    {
        if (getRelativePositionFromObject(object).y != 0)
        {
            setRelativePositionFromObject(object, {object->position.x, 0});
            object->rising = false;
        }
        velModifier = object->velocity.y = 0;
        return 1;
    }

    return 0;
}
int Game::updateMovement()
{
    for (auto &i : platforms)
    {
        // i->position.x -= 1;
    }
    return 0;
};

int Game::spawnPlatform()
{
    LOG_INFO("Spawning platform");
    int sizeOfVec = platforms.size();
    platforms.push_back(new Platform({window->getSize().x, window->getSize().y - 100}, type::Vector2i(500, 100), {100, 100, 100}));
    LOG_INFO("Platform added to vector in position \"" + std::to_string(platforms.size() - 1) + "\"");
    if (sizeOfVec - platforms.size() == 0)
    {
        return -1;
    }
    return 0;
}

void Game::removePlatform()
{
    // if( !platforms.empty() && getRelativePositionFromObject(platforms[0]).x <= 0){
    //     delete *platforms.begin();
    //     platforms.erase(platforms.begin());
    //     LOG_INFO("Platform removed from vector in position 0");
    // }
}

int Game::update()
{
    int r = updateGravity(player);

    int rt = updateMovement();

    removePlatform();
    printPlatform();
    return std::min(r, rt);
}

void Game::printPlatform()
{
    for (int i = 0; i < platforms.size(); ++i)
    {
        // LOG_INFO("Platfrom \"" + std::to_string(i) + "\" is in position x:" + std::to_string(platforms[i]->position.x) + ", y:" + std::to_string(platforms[i]->position.y));
    }
}

void Game::updateObjectLocation(ObjectBase *object)
{
    object->dst.x = object->position.x;
    object->dst.y = object->position.y;
}