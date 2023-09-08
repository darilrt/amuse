#pragma once

#include "amuse/wm.h"

class Screen {
public:
    wm::Window* window;

    static Screen* Get() {
        static Screen instance;
        return &instance;
    }

    static inline int GetWidth() { return Get()->window->GetWidth(); }
    
    static inline int GetHeight() { return Get()->window->GetHeight(); }

private:
    Screen() {}
    ~Screen() {}
};