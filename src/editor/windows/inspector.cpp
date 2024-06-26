#include "editor/windows/inspector.hpp"
#include "amuse/editor.hpp"
#include "amuse/gui.hpp"
#include "icons.hpp"

void draw_component_helpers(Actor *actor, Editor *editor)
{
    std::vector<Shared<Component>> to_remove;

    for (auto &component : actor->components)
    {
        ImGui::PushID(component.get());
        ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(4, 0));
        ImGui::Checkbox("##", &component->enabled);
        ImGui::SameLine();

        bool open = ImGui::TreeNodeEx(component->_name.c_str(), ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_SpanFullWidth | ImGuiTreeNodeFlags_AllowOverlap);
        ImGui::SameLine(ImGui::GetContentRegionMax().x - 20);
        if (ImGui::Button("×"))
        {
            editor->set_status(
                [component](Editor *editor)
                { ImGui::Text("Deleted component: %s", component->_name.c_str()); });

            to_remove.push_back(component);
            editor->set_edited();
        }
        ImGui::PopStyleVar();

        if (open)
        {
            ImGui::TreePop();

            component->on_inspector();
        }
        ImGui::PopID();

        ImGui::Separator();
    }

    for (auto &component : to_remove)
    {
        actor->remove_component(component);
    }
}

void InspectorEditor::on_init()
{
}

void InspectorEditor::on_gui()
{
    if (editor->selected_actor == nullptr)
        return;

    char buffer[256];
    strcpy_s(buffer, editor->selected_actor->name.c_str());

    auto height = (ImGui::CalcTextSize("Name").y + ImGui::GetStyle().FramePadding.y * 2.0) / 2.0f - icon_size / 2.0f;

    auto style = ImGui::GetStyle();
    ImGui::SetCursorPosY(ImGui::GetCursorPosY() + height);
    ImGui::Image(ICON_OBJECT);
    ImGui::SameLine();
    ImGui::SetCursorPosY(ImGui::GetCursorPosY() - height);
    if (ImGui::InputText("Name", buffer, 256, ImGuiInputTextFlags_EnterReturnsTrue))
    {
        editor->selected_actor->name = buffer;
        editor->set_edited();
    }
    ImGui::Separator();

    draw_component_helpers(editor->selected_actor.get(), editor);

    if (ImGui::Button("Add Component", ImVec2(-1, 0)))
    {
        ImGui::OpenPopup("Add Component");
    }

    if (ImGui::BeginPopup("Add Component"))
    {
        for (auto &pair : editor->engine->component_registry->factories)
        {
            if (ImGui::MenuItem(pair.first.c_str()))
            {
                auto component = pair.second();
                editor->selected_actor->add_component(component);
                editor->set_edited();
            }
        }

        ImGui::EndPopup();
    }
}