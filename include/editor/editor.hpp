#pragma once

#include <unordered_map>
#include <filesystem>
#include <string>

#include "core/engine.hpp"
#include "core/actor.hpp"
#include "editor/editor_window.hpp"
#include "types.hpp"

struct EditorWindowState
{
    bool is_open = true;
    Shared<EditorWindow> window;
};

class Editor
{
public:
    Shared<Actor> selected_actor;
    std::string current_project_path;
    Engine *engine;
    std::unordered_map<std::string, EditorWindowState> windows;

    template <typename T>
    void register_window(const std::string &name)
    {
        windows[name] = {};
        windows[name].is_open = true;
        windows[name].window = Shared<EditorWindow>(new T());
        windows[name].window->name = name;
        windows[name].window->editor = this;
    }

    template <typename T>
    Shared<T> get_window(const std::string &name)
    {
        return std::static_pointer_cast<T>(windows[name].window);
    }

    void open(const std::filesystem::path &path);

    void load_actor(const std::filesystem::path &path);

    void run();
};