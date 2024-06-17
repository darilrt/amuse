#include "engine/canvas.hpp"

Canvas::Canvas(Vec2i size, Vec2i position)
{
    set_size(size);
    set_position(position);
}

void Canvas::set_size(Vec2i size)
{
    this->size = size;
    _projection = Mat4::ortho(0.0f, (float)size.x, (float)size.y, 0.0f, -1.0f, 1.0f);
}

void Canvas::set_position(Vec2i position)
{
    this->position = position;
    _view = Mat4::identity();
    _view.translate(Vec3(position.x, position.y, 0));
}