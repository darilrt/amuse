#pragma once

#include "engine/math.hpp"

class Rect
{
public:
    Vec2 position;
    Vec2 size;

    Rect() = default;

    Rect(const Vec2 &position, const Vec2 &size)
        : position(position), size(size)
    {
    }

    bool contains(const Vec2 &point) const
    {
        return point.x >= position.x && point.x <= position.x + size.x &&
               point.y >= position.y && point.y <= position.y + size.y;
    }

    bool intersects(const Rect &other) const
    {
        return position.x < other.position.x + other.size.x &&
               position.x + size.x > other.position.x &&
               position.y < other.position.y + other.size.y &&
               position.y + size.y > other.position.y;
    }
};
