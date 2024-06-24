#include "editor/windows/visual_component.hpp"
#include "editor/editor.hpp"
#include "imgui/imgui.h"

void VisualComponentEditor::on_init()
{
}

void VisualComponentEditor::on_gui()
{
    ImGuiIO &io = ImGui::GetIO();
    ImGuiStyle style = ImGui::GetStyle();

    ImVec2 pos = ImGui::GetCursorScreenPos();
    ImVec2 start = ImGui::GetCursorScreenPos();
    start.x -= style.WindowPadding.x;
    start.y -= style.WindowPadding.y;

    ImVec2 end = ImGui::GetWindowContentRegionMax();
    end.x += pos.x;
    end.y += pos.y;

    ImDrawList *draw_list = ImGui::GetWindowDrawList();

    const ImVec4 &color1 = ImVec4(0.08f, 0.08f, 0.08f, 1.00f);
    const ImVec4 &color2 = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
    const ImVec4 &color3 = ImVec4(0.19f, 0.19f, 0.19f, 1.00f);
    const ImVec4 &color4 = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);

    draw_list->AddRectFilled(start, end, IM_COL32(36, 36, 36, 255));

    constexpr ImU32 GRID_COLOR = IM_COL32(20, 20, 20, 60);

    ImVec2 position = ImVec2(0, 0);
    float size = 32.0f;

    for (float x = fmodf(-position.x, size); x < io.DisplaySize.x; x += size)
    {
        draw_list->AddLine(ImVec2(start.x + x, start.y), ImVec2(start.x + x, end.y), GRID_COLOR);
    }

    for (float y = fmodf(-position.y, size); y < io.DisplaySize.y; y += size)
    {
        draw_list->AddLine(ImVec2(start.x, start.y + y), ImVec2(end.x, start.y + y), GRID_COLOR);
    }
}