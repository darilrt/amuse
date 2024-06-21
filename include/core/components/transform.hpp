#pragma once

#include "core/component.hpp"
#include "engine/math.hpp"

class Transform : public Component
{
public:
    Vec3 position;
    Quat rotation;

    Transform();

    void on_inspector() override;
};