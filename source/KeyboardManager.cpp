#include "KeyboardManager.h"
#include "Logger.h"

KeyboardManager* KeyboardManager::instance = nullptr;
const Uint8* KeyboardManager::state = SDL_GetKeyboardState(NULL);
KeyboardManager* KeyboardManager::getInstance(){
    if (instance == nullptr){
        instance = new KeyboardManager();
    } 
    return instance;
}

bool KeyboardManager::isPressed(SDL_Keycode key){
    return state[key];
}

const Uint8 *KeyboardManager::getKeyboardStatus(){
    return state;
}
