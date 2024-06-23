#include "core/components/transform.hpp"
#include "editor/ui.hpp"

Transform::Transform()
{
}

float center = 0.35;

void Transform::on_inspector()
{
    ui::InputVector3("Position", &position.x);

    if (ui::InputVector3("Rotation", &_euler_angles.x))
    {
        rotation = Quat::from_euler(math::rad(_euler_angles));
    }

    ui::InputVector3("Scale", &scale.x);
}