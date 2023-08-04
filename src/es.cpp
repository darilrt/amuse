#include "es.h"

#include <iostream>

SDL_Event es::event;
es::Event es::e;
std::unordered_map<std::string, std::vector<std::function<void(const es::Event& e)>>> es::callbacks;

void es::PollEvents() {
    es::TriggerEvent("Tick");

    while (SDL_PollEvent(&es::event)) {
        switch (es::event.type) {
        case SDL_QUIT:
            TriggerEvent("Quit");
            break;

        case SDL_KEYDOWN:
            e.keyCode = (KeyCode)event.key.keysym.scancode;
            TriggerEvent("KeyDown");
            break;
        
        case SDL_KEYUP:
            e.keyCode = (KeyCode)event.key.keysym.scancode;
            TriggerEvent("KeyUp");
            break;
        
        case SDL_MOUSEBUTTONDOWN:
            e.mouse.button = (MouseButton) (event.button.button - 1);
            TriggerEvent("MouseDown");
            break;
        
        case SDL_MOUSEBUTTONUP:
            e.mouse.button = (MouseButton) (event.button.button - 1);
            TriggerEvent("MouseUp");
            break;
        
        case SDL_MOUSEMOTION:
            e.mouse.delta.x = event.motion.xrel;
            e.mouse.delta.y = event.motion.yrel;
            e.mouse.position.x = event.motion.x;
            e.mouse.position.y = event.motion.y;
            TriggerEvent("MouseMotion");
            break;
        }

        switch (es::event.window.event) {
        case SDL_WINDOWEVENT_RESIZED:
            e.window.width = event.window.data1;
            e.window.height = event.window.data2;
            TriggerEvent("Resize");
            break;
        }
    }
}

void es::AddEventListener(std::string name, std::function<void(const Event& e)> callback) {
    es::callbacks[name].push_back(callback);
}

void es::TriggerEvent(std::string name) {
    for (auto &callback : es::callbacks[name]) {
        callback(e);
    }
}
