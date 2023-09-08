#include "amuse/singletons/input.h"
#include "amuse/es.h"

#include <algorithm>

Input* Input::instance;

Input::Input() {
    keys.fill(false);

    es::AddEventListener("Tick", [&](const es::Event& e) {
        deltaTime = deltaTimer.Reset();

        keysDown.fill(false);
        keysUp.fill(false);
        mouseButtons.fill(false);
        mouseButtonsDown.fill(false);
        mouseButtonsUp.fill(false);
        mouseDelta = {0, 0};
    });

    es::AddEventListener("KeyDown", [&](const es::Event& e) {
        keys[(uint16_t)e.keyCode] = true;
        keysDown[(uint16_t)e.keyCode] = true;
    });

    es::AddEventListener("KeyUp", [&](const es::Event& e) {
        keys[(uint16_t)e.keyCode] = false;
        keysUp[(uint16_t)e.keyCode] = true;
    });

     es::AddEventListener("MouseDown", [&](const es::Event& e) {
         mouseButtons[(uint16_t)e.mouse.button] = true;
         mouseButtonsDown[(uint16_t)e.mouse.button] = true;
     });

     es::AddEventListener("MouseUp", [&](const es::Event& e) {
         mouseButtons[(uint16_t)e.mouse.button] = false;
         mouseButtonsUp[(uint16_t)e.mouse.button] = true;
     });

    es::AddEventListener("MouseMotion", [&](const es::Event& e) {
        mousePosition = e.mouse.position;
        mouseDelta = e.mouse.delta;
    });
}

Input& Input::GetInstance() {
    if (!instance) {
        instance = new Input();
    }
    return *instance;
}
