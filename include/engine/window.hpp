#pragma once

#include <SDL2/SDL.h>

#include "engine/event_system.hpp"
#include "engine/key_code.hpp"
#include "engine/math.hpp"

Event(WindowResize {
    int width;
    int height;
});
Event(WindowClose);

Event(KeyDown {
    KeyCode key_code;
});
Event(KeyUp {
    KeyCode key_code;
});

// Mouse events
Event(MouseMove {
    int x;
    int y;
    int dx;
    int dy;
});
Event(MouseButtonDown {
    MouseButton button;
});
Event(MouseButtonUp {
    MouseButton button;
});
Event(MouseScroll {
    int x;
    int y;
});

enum class VSync : int
{
    Off = 0,
    On = 1,
};

struct Window
{
    uint32_t id;
    SDL_Window *sdl_window;
    SDL_GLContext gl_context;
    SDL_Event event;
    bool is_open = true;

    Window(const std::string &title, int width, int height);

    ~Window();

    void poll_events(EventSystem &es);

    void swap_buffers();

    void set_title(const std::string &title);

    inline void quit() { is_open = false; }

    void set_vsync(VSync vsync);

    void set_resizable(bool resizable);

    void maximize();

    Vec2i get_size();
};