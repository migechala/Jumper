#ifndef KEYBOARD_MANAGER_H
#define KEYBOARD_MANAGER_H
#include <SDL.h>
#include <map>

class KeyboardManager
{
    static const Uint8 *state;
    std::multimap<std::pair<SDL_Scancode, bool>, std::pair<std::function<void()>, bool>> listeners;
    static KeyboardManager *instance;
    static bool listen;

public:
    static KeyboardManager *getInstance();
    const Uint8 *getKeyboardStatus();
    void addListener(SDL_Scancode key, std::function<void()> func, bool lock);
    void removeListener(SDL_Scancode key);

    void printListner();

    bool isPressed(SDL_Scancode key);
    void update();
    void onListners();
    void offListners();

    std::vector<int> getAllPressed();
};

#endif