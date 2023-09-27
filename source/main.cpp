#include <SDL.h>
#include "Logger.h"
#include "ResourceLoader.h"
#include "WindowManager.h"
#include "KeyboardManager.h"
#include "Game.h"
#include "Objects.h"
#define CHECK(func, tar, var)       \
    {                               \
        if (func != tar)            \
        {                           \
            var = !var;             \
            LOG_ERR(SDL_GetError()) \
        }                           \
    }
int main()
{
    SDL_Init(SDL_INIT_EVERYTHING);
    Logger::resetLogger();
    std::string logTest = std::to_string(100);
    if (logTest != "100")
    {
        LOG_ERR("To string returns wrong value, should be 100, returns " + logTest);
    }
    WindowManager *windowManager = new WindowManager("Jumper", type::Vector2i(SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED), SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    windowManager->setBackground(ResourceLoader::getInstance()->loadTexture("../assets/background/bkg_a.jpg", windowManager->getRenderer()));
    Player *player = new Player(windowManager->getSize() / 3, type::Vector2i(100, 100), {100, 0, 100}, windowManager->getSize().x);
    Game *game = new Game(windowManager, player);
    game->spawnPlatform();
    game->spawnPlatform({player->position.x, player->position.y - player->size.y}, {100, 20});
    bool done = false;
    bool died = false;
    while (!done)
    {
        Uint32 start = SDL_GetPerformanceCounter();
        // Do loops
        CHECK(windowManager->update(), false, done); // false because true will exit
        if (!died && game->update() == 0)
        {
            windowManager->draw(player);
            game->updateObjectLocation(player);
        }
        else
        {
            died = true;
            player->removeControl();
            KeyboardManager::getInstance()->addListener(
                SDL_SCANCODE_R, [&]
                {
                    if(died){
                    player = new Player(windowManager->getSize() / 3, type::Vector2i(100, 100), {100, 0, 100}, windowManager->getSize().x);
                    game = new Game(windowManager, player); 
                    game->spawnPlatform();
                    game->spawnPlatform({player->position.x, player->position.y - player->size.y}, {100, 20});
                    died = false; 
                    } },
                false);
        }

        KeyboardManager::getInstance()->update();
        // player->update();
        // Limit fps
        Uint32 end = SDL_GetPerformanceCounter();
        float elapsedMS = (end - start) / (float)SDL_GetPerformanceFrequency() * 1000.0f;
        SDL_Delay(floor(16.666f - elapsedMS)); // 16 2/3 miliseconds in between frame AKA, cap at 60 fps
    }
    return 0;
}