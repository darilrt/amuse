#pragma once

#include "engine/math.hpp"

class Bounds
{
public:
    Vec3 min, max;

    Bounds();

    Bounds(Vec3 _min, Vec3 _max);

    bool intersects(const Bounds &other);

    bool contains(const Vec3 &point);

    Vec3 get_center();

    Vec3 get_size();

    Vec3 get_closest_point(const Vec3 &point);

    static Bounds from_min_max(Vec3 min, Vec3 max);
};