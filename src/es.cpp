#include "amuse/es.h"

#ifdef AMUSE_USE_IMGUI
#include "imgui.h"
#include "imgui_impl_sdl2.h"
#endif

#include <iostream>

SDL_Event es::event;
bool es::ignoreGui = false;
es::Event es::e;
std::unordered_map<std::string, std::vector<std::function<void(const es::Event& e)>>> es::callbacks;

void es::PollEvents() {
    es::TriggerEvent("Tick");

    while (SDL_PollEvent(&es::event)) {

#ifdef AMUSE_USE_IMGUI
        ImGui_ImplSDL2_ProcessEvent(&es::event);
#endif
        
        switch (es::event.type) {
        case SDL_QUIT:
            TriggerEvent("Quit");
            break;

        case SDL_KEYDOWN:
            e.keyCode = (KeyCode)event.key.keysym.scancode;
                
#ifdef AMUSE_USE_IMGUI
            if (ImGui::GetIO().WantCaptureKeyboard && !ignoreGui) { break; }
#endif

            TriggerEvent("KeyDown");
            break;
        
        case SDL_KEYUP:
            e.keyCode = (KeyCode)event.key.keysym.scancode;

#ifdef AMUSE_USE_IMGUI
            if (ImGui::GetIO().WantCaptureKeyboard && !ignoreGui) { break; }
#endif

            TriggerEvent("KeyUp");
            break;
        
        case SDL_MOUSEBUTTONDOWN:
            e.mouse.button = (MouseButton) (event.button.button - 1);

#ifdef AMUSE_USE_IMGUI
            if (ImGui::GetIO().WantCaptureMouse && !ignoreGui) { break; }
#endif

            TriggerEvent("MouseDown");
            break;
        
        case SDL_MOUSEBUTTONUP:
            e.mouse.button = (MouseButton) (event.button.button - 1);

#ifdef AMUSE_USE_IMGUI
            if (ImGui::GetIO().WantCaptureMouse && !ignoreGui) { break; }
#endif

            TriggerEvent("MouseUp");
            break;
        
        case SDL_MOUSEMOTION:
            e.mouse.delta.x = event.motion.xrel;
            e.mouse.delta.y = event.motion.yrel;
            e.mouse.position.x = event.motion.x;
            e.mouse.position.y = event.motion.y;

#ifdef AMUSE_USE_IMGUI
            if (ImGui::GetIO().WantCaptureMouse && !ignoreGui) { break; }
#endif

            TriggerEvent("MouseMotion");
            break;
        
        case SDL_WINDOWEVENT:
            switch (event.window.event) {
            case SDL_WINDOWEVENT_RESIZED:
                e.window.width = event.window.data1;
                e.window.height = event.window.data2;
                TriggerEvent("WindowResize");
                break;
            }
            break;
        }
    }
}

void es::AddEventListener(std::string name, std::function<void(const Event& e)> callback) {
    if (es::callbacks.find(name) == es::callbacks.end()) {
        es::callbacks[name] = std::vector<std::function<void(const Event& e)>>();
    }

    es::callbacks[name].push_back(callback);
}

void es::TriggerEvent(std::string name) {
    if (es::callbacks.find(name) == es::callbacks.end()) {
		return;
	}

    for (auto &callback : es::callbacks[name]) {
        callback(e);
    }
}
