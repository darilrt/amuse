#include "input.h"
#include "es.h"

#include <algorithm>

Input Input::instance;

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
}