#pragma once

#include <map>

#include "engine/math.hpp"
#include "engine/font.hpp"

class Canvas
{
public:
    Vec2i size;
    Vec2i position;
    Mat4 _projection;
    Mat4 _view;

    Canvas(Vec2i size, Vec2i position);

    void set_size(Vec2i size);

    void set_position(Vec2i position);
};