#include "editor/windows/scene.hpp"
#include "amuse/gui.hpp"
#include "icons.hpp"

void SceneEditor::on_init()
{
}

void SceneEditor::on_gui()
{
    auto style = ImGui::GetStyle();

    ImVec2 start = ImGui::GetWindowContentRegionMin();

    ImVec2 size = ImGui::GetWindowContentRegionMax();
    size.x -= ImGui::GetWindowContentRegionMin().x;
    size.y -= ImGui::GetWindowContentRegionMin().y;

    ImGui::SetCursorPos(start);

    ImGui::Image((void *)0, ImVec2(size.x, size.y), ImVec2(0, 0), ImVec2(1, 1));

    start.x += 10;
    start.y += 10;
    ImGui::SetCursorPos(start);

    if (ImGui::ImageButton(ICON_PLACEHOLDER))
    {
    }

    ImGui::SameLine();

    if (ImGui::ImageButton(ICON_PLACEHOLDER))
    {
    }

    ImGui::SameLine();

    if (ImGui::ImageButton(ICON_PLACEHOLDER))
    {
    }
}

void SceneEditor::on_push_style()
{
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
}

void SceneEditor::on_pop_style()
{
    ImGui::PopStyleVar();
}