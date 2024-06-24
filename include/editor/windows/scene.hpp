#pragma once

#include "editor/editor_window.hpp"

class SceneEditor : public EditorWindow
{
public:
    void on_init() override;

    void on_gui() override;

    void on_push_style() override;

    void on_pop_style() override;
};
