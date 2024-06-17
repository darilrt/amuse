#pragma once

#include "editor/editor_window.hpp"

class SceneEditor : public EditorWindow
{
public:
    void init() override;

    void on_gui() override;
};
