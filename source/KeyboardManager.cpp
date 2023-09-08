#include "KeyboardManager.h"
#include "Logger.h"

KeyboardManager *KeyboardManager::instance = nullptr;
bool KeyboardManager::listen = true;

const Uint8 *KeyboardManager::state = SDL_GetKeyboardState(NULL);
KeyboardManager *KeyboardManager::getInstance()
{

    if (instance == nullptr)
    {
        instance = new KeyboardManager();
    }
    return instance;
}
void KeyboardManager::addListener(SDL_Scancode key, std::function<void()> func, bool lock)
{
    listeners.insert({std::make_pair(key, lock), std::make_pair(func, false)});
}

bool KeyboardManager::isPressed(SDL_Scancode key)
{
    return state[key];
}

void KeyboardManager::onListners()
{
    listen = true;
}

void KeyboardManager::printListner()
{
    LOG_INFO("____________________________");
    for (auto &i : listeners)
    {
        LOG_INFO("| " + std::string(SDL_GetKeyName(SDL_GetKeyFromScancode(i.first.first))) + " | func | " + std::to_string(i.second.second) + " |");
    }
    LOG_INFO("----------------------------");
}

void KeyboardManager::offListners()
{
    listen = false;
}

const Uint8 *KeyboardManager::getKeyboardStatus()
{
    return state;
}

std::vector<int> KeyboardManager::getAllPressed()
{
    std::vector<int> pressed;
    for (int i = 0; i < sizeof(state) / state[0]; ++i)
    {
        if (state[i])
        {
            pressed.emplace_back(i);
        }
    }
    return pressed;
}

void KeyboardManager::removeListener(SDL_Scancode key)
{
    listeners.erase({key, false});
    listeners.erase({key, true});
}

void KeyboardManager::update()
{
    if (!listen)
    {
        return;
    }
    for (auto &i : listeners)
    {
        /*
         * i->first is the scancode key
         * i->second will return the std::pair of the function that will be ran and the lock state
         * i->second->first is the function that will be ran
         * i->second->second is the lock state of the key
         */
        if (state[i.first.first] && (!i.first.second || !i.second.second))
        {
            i.second.first();
            i.second.second = true; // lock
        }
        else if (!state[i.first.first] && i.second.second)
        {
            i.second.second = false; // unlock
        }
    }
}
