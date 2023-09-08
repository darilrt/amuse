#include "amuse/input.h"
#include "amuse/es.h"

#include <algorithm>
#include "input.h"

Input* Input::instance;

Input::Input() {
    keys.fill(false);
    
    es::AddEventListener("Tick", [&](const es::Event& e) {
        deltaTime = deltaTimer.Reset();
        
        keysDown.fill(false);
		keysUp.fill(false);
    });
    
    es::AddEventListener("KeyDown", [&](const es::Event& e) {
        keys[(uint16_t)e.keyCode] = true;
        keysDown[(uint16_t)e.keyCode] = true;
    });

    es::AddEventListener("KeyUp", [&](const es::Event& e) {
        keys[(uint16_t)e.keyCode] = false;
        keysUp[(uint16_t)e.keyCode] = true;
    });

    // es::AddEventListener("MouseButtonDown", [&](const es::Event& e) {
    //     mouseButtons[(uint16_t)e.mouseButton] = true;
    //     mouseButtonsDown[(uint16_t)e.mouseButton] = true;
    // });

    // es::AddEventListener("MouseButtonUp", [&](const es::Event& e) {
    //     mouseButtons[(uint16_t)e.mouseButton] = false;
    //     mouseButtonsUp[(uint16_t)e.mouseButton] = true;
    // });

    es::AddEventListener("MouseMotion", [&](const es::Event& e) {
        mousePosition = e.mouse.position;
    });
}

Input& Input::GetInstance() {
    if (!instance) {
		instance = new Input();
	}
    return *instance;
}
