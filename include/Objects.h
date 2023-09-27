#pragma once
#include "Types.h"

struct ObjectBase
{
    ObjectBase(type::Vector2i position, type::Vector2i size, SDL_Color color);
    type::Vector2i position;
    type::Vector2i velocity;
    type::Vector2i size;
    SDL_Rect dst;
    SDL_Color color;
    bool rising;
};

class Player : public ObjectBase
{
    int jumpHeight, frameEnd, maxWidth;
    void up();
    void down();
    void left();
    void right();

public:
    Player(type::Vector2i position, type::Vector2i size, SDL_Color color, int maxWidth);
    void removeControl();
    void enableControl();
    int update();
    int jump();
};

class Platform : public ObjectBase
{
public:
    Platform(type::Vector2i position, type::Vector2i size, SDL_Color color, int speed);
};