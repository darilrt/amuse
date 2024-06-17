#pragma once

#include "types.hpp"
#include "engine/math.hpp"

class Transform
{
public:
    Shared<Transform> parent;
    Vec3 position;
    Quat rotation = Quat();
    Vec3 scale = Vec3(1.0f);

    Mat4 get_matrix() const;

    Mat4 get_inverse_matrix() const;

    void look_at(const Vec3 &target, const Vec3 &up = Vec3(0, 1, 0));

    Vec3 forward();

    Vec3 right();

    Vec3 up();
};