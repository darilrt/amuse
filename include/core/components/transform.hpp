#pragma once

#include "core/component.hpp"
#include "engine/math.hpp"

class Transform : public Component
{
public:
    Vec3 position;
    Quat rotation;
    Vec3 _euler_angles;
    Vec3 scale;

    Transform();

    void on_inspector() override;
};