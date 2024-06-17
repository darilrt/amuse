#include "engine/bounds.hpp"

Bounds::Bounds() : min(Vec3()), max(Vec3())
{
}

Bounds::Bounds(Vec3 _min, Vec3 _max) : min(_min), max(_max)
{
}

bool Bounds::intersects(const Bounds &other)
{
    return min.x <= other.max.x && max.x >= other.min.x && min.y <= other.max.y && max.y >= other.min.y && min.z <= other.max.z && max.z >= other.min.z;
}

bool Bounds::contains(const Vec3 &point)
{
    return point.x >= min.x && point.x <= max.x && point.y >= min.y && point.y <= max.y && point.z >= min.z && point.z <= max.z;
}

Vec3 Bounds::get_center()
{
    return (min + max) / 2.0f;
}

Vec3 Bounds::get_size()
{
    return max - min;
}

Vec3 Bounds::get_closest_point(const Vec3 &point)
{
    return Vec3(
        math::clamp(point.x, min.x, max.x),
        math::clamp(point.y, min.y, max.y),
        math::clamp(point.z, min.z, max.z));
}

Bounds Bounds::from_min_max(Vec3 min, Vec3 max)
{
    return Bounds(min, max);
}
