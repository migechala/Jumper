#include "Game.h"
#include "Objects.h"
#include "Logger.h"
#include <algorithm>
#include <cmath>
#include <random>
#include <set>
#include <ctime>

Game::Game(WindowManager *window, Player *player) : window(window), player(player), platformDistance(100), platformIndex(0)
{
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
}

int Game::updateGravity(ObjectBase *object)
{
    int collideY = (platformIndex != 0) ? (-1 * object->size.y) : 0;
    int collideV = 0;
    for (int i = platforms.size() - 1; i >= 0; --i)
    {
        type::Vector2i position = platforms[i]->position;
        if (object->position.y >= position.y && (object->position.x + object->size.x > position.x && object->position.x < position.x + platforms[i]->size.x) && collideY < position.y + platforms[i]->size.y)
        {
            {
                collideY = position.y + platforms[i]->size.y;
                collideV = platforms[i]->velocity.x;
            }
        }
    }

    if ((object->position.y + object->velocity.y - (velModifier + 0.1) < collideY || object->position.y + object->velocity.y - (velModifier + 0.1) < collideY - object->size.y / 2) && !object->rising)
    {
        if (object->position.y != collideY)
        {
            window->setPosition(object, {object->position.x, collideY});
        }

        object->velocity.x = collideV;
        velModifier = object->velocity.y = 0;
    }
    else
    {
        velModifier += 0.1;
        object->velocity.y -= velModifier;
        if (object->velocity.y <= 0)
        {
            object->rising = false;
        }
        if (object->velocity.y > 0 && object->position.y >= window->getSize().y / 2)
        {
            for (auto *i : platforms)
            {
                i->position.y -= abs(object->velocity.y);
                if (platformIndex == 0)
                {
                    platforms.erase(platforms.end() - 1);
                }
                ++platformIndex;
            }
        }
        else
        {
            object->position.y += object->velocity.y;
        }
    }
    object->position.x += object->velocity.x;
    return 0;
}

int Game::spawnPlatform()
{
    LOG_INFO("Spawning platform");
    int sizeOfVec = platforms.size();

    for (int i = 0; i < window->getSize().y / 100; ++i)
    {
        SDL_Color color = {(Uint8)genrateRandom(0, 255),
                           (Uint8)genrateRandom(0, 255),
                           (Uint8)genrateRandom(0, 255)};
        platforms.push_back(new Platform({genrateRandom(0, window->getSize().x - 400),
                                          platformDistance * i},
                                         type::Vector2i(genrateRandom(100, 200), 20),
                                         color,
                                         genrateRandom(1, 4)));
    }

    LOG_INFO("Platform added to vector in position \"" + std::to_string(platforms.size() - 1) + "\"");
    if (sizeOfVec - platforms.size() == 0)
    {
        return -1;
    }
    return 0;
}

void Game::spawnPlatform(type::Vector2i position, type::Vector2i size)
{
    SDL_Color color = {(Uint8)genrateRandom(0, 255),
                       (Uint8)genrateRandom(0, 255),
                       (Uint8)genrateRandom(0, 255)};
    platforms.emplace_back(new Platform(position,
                                        size,
                                        color,
                                        genrateRandom(1, 4)));
}

int Game::genrateRandom(int min, int max)
{

    return std::rand() % (max + 1) + min;
}

int Game::update()
{
    updateGravity(player);

    updatePlatforms();
    printPlatform();
    return checkLose(player);
}

void Game::updatePlatforms()
{
    int index = 0;
    for (Platform *i : platforms)
    {
        i->position.x += i->velocity.x;
        if (i->position.x <= 0 || i->position.x + i->size.x >= window->getSize().x)
        {
            i->velocity.x *= -1;
        }
        if (i->position.y < 0)
        {
            platforms[index] = new Platform({genrateRandom(0, window->getSize().x - 200),
                                             platformDistance * static_cast<int>(platforms.size())},
                                            type::Vector2i(genrateRandom(100, 200), 20),
                                            {(Uint8)genrateRandom(0, 255),
                                             (Uint8)genrateRandom(0, 255),
                                             (Uint8)genrateRandom(0, 255)},
                                            genrateRandom(1, 4));
        }
        ++index;
    }
}

int Game::checkLose(ObjectBase *object)
{
    return (object->position.y == -1 * object->size.y) ? -1 : 0;
}

void Game::printPlatform()
{
    for (int i = 0; i < platforms.size(); ++i)
    {
        window->draw(platforms[i]);
    }
}

void Game::updateObjectLocation(ObjectBase *object)
{
    object->dst.x = object->position.x;
    object->dst.y = object->position.y;
}