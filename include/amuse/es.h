#pragma once

#include "amuse/enums.h"
#include "amuse/singletons/input.h"

#include <glm/glm.hpp>
#include <SDL.h>
#include <vector>
#include <unordered_map>
#include <string>
#include <functional>

class es {
public:
    struct Event {
        struct {
            int32_t width;
            int32_t height;
        } window;

        KeyCode keyCode;

        struct {
            MouseButton button;
            glm::vec2 delta;
            glm::vec2 position;
            glm::vec2 wheel;
        } mouse;
    };

    static void PollEvents();

    static void AddEventListener(std::string name, std::function<void(const Event& e)> callback);

    static void TriggerEvent(std::string name);

private:
    static SDL_Event event;
    static bool ignoreGui;
    static Event e;

    static std::unordered_map<std::string, std::vector<std::function<void(const Event& e)>>> callbacks;
};
