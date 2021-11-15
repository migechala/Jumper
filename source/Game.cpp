#include "Game.h"
#include "Objects.h"
#include "Logger.h"
#include <cmath>

Game::Game(WindowManager* window, Player* player): window(window), player(player){
    
}

type::Vector2i Game::getRelativePositionFromObject(ObjectBase* object){
    return window->getSize() - (object->size + object->position);
}

int Game::updateGravity(ObjectBase* object){
    if(getRelativePositionFromObject(object).y > - object->size.y){
        velModifier += -0.1;
    }
    else{
        if(object->velocity.y + -0.1 < 0){
            velModifier = object->velocity.y = 0;
            return 1;
        }
    }

    object->velocity.y += velModifier;
    object->position.y -= object->velocity.y;

    object->dst.y = object->position.y;
    object->dst.x = object->position.x;
    return 0;
}
int Game::updateMovement(){
    for(auto &i : platforms){
        i->position.x -=1 ;
    }
    return 0;
};

int Game::spawnPlatform(){
    LOG_INFO("Spawning platform");
    int sizeOfVec = platforms.size();
    platforms.push_back(new Platform({window->getSize().x, window->getSize().y - 100}, type::Vector2i(500, 100), {100, 100, 100}));
    LOG_INFO("Platform added to vector in position \"" + std::to_string(platforms.size() - 1) + "\"");
    if(sizeOfVec - platforms.size() == 0){
        return -1;
    }
    return 0;
}

void Game::removePlatform(){
    if( !platforms.empty() && getRelativePositionFromObject(platforms[0]).x <= 0){
        delete *platforms.begin();
        platforms.erase(platforms.begin());
        LOG_INFO("Platform removed from vector in position 0");
    }
}

int Game::update(){
    int r = updateGravity(player);
    
    int rt = updateMovement();
    
    removePlatform();

    return std::min(r, rt);
}