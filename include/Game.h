#pragma once
#include <Logger.h>
#include <vector>
#include "WindowManager.h"
#include "Objects.h"
class Game
{
    std::vector<Platform *> platforms;
    Player *player;
    WindowManager *window;
    double velModifier;
    int platformDistance;
    int platformIndex;
    int updateGravity(ObjectBase *object);
    int genrateRandom(int min, int max);
    void updatePlatforms();
    int checkLose(ObjectBase *object);

public:
    Game(WindowManager *window, Player *player);
    int spawnPlatform();
    void spawnPlatform(type::Vector2i position, type::Vector2i size);
    int update();
    void updateObjectLocation(ObjectBase *object);
    void printPlatform();
};