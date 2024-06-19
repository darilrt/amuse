#include "editor/windows/inspector.hpp"
#include "amuse/editor.hpp"
#include "amuse/gui.hpp"

void InspectorEditor::init()
{
}

void InspectorEditor::on_gui()
{
    if (editor->selected_actor == nullptr)
        return;

    char buffer[256];
    strcpy_s(buffer, editor->selected_actor->name.c_str());

    if (ImGui::InputText("Name", buffer, 256, ImGuiInputTextFlags_EnterReturnsTrue))
    {
        editor->selected_actor->name = buffer;
        editor->set_edited();
    }
}