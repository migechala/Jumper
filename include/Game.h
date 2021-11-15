#pragma once
#include <Logger.h>
#include <vector>
#include "WindowManager.h"
#include "Objects.h"
class Game{
    std::vector<Platform*> platforms;
    Player* player;
    WindowManager* window;
    double velModifier;
    int updateGravity(ObjectBase* object);
    int updateMovement();
    void removePlatform();
public:
    Game(WindowManager* window,Player* player);
    type::Vector2i getRelativePositionFromObject(ObjectBase* object);
    int spawnPlatform();
    int update();
};