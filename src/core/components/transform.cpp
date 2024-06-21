#include "core/components/transform.hpp"
#include "imgui/imgui.h"

Transform::Transform()
{
}

void Transform::on_inspector()
{
    ImGui::Text("Position");
}