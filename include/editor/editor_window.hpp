#pragma once

#include <string>

#include "core/actor.hpp"
#include "types.hpp"

class Editor;

class EditorWindow
{
public:
    Ptr<Editor> editor;
    std::string name;

    virtual void init() = 0;

    virtual void on_gui() = 0;

    virtual void on_push_style() {};

    virtual void on_pop_style() {};
};