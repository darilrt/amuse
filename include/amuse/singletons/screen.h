#pragma once

#include "amuse/core.h"

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