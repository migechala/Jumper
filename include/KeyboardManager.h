#ifndef KEYBOARD_MANAGER_H
#define KEYBOARD_MANAGER_H
#include <SDL2/SDL.h>
class KeyboardManager{
    static const Uint8 *state;
    static KeyboardManager* instance;
public:
    static KeyboardManager* getInstance();
    const Uint8 *getKeyboardStatus();
    bool isPressed(SDL_Keycode key);
};

#endif