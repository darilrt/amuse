#pragma once

#include <vector>

#include "engine/graphics/texture.hpp"
#include "engine/math.hpp"

class Font
{
public:
    void *cdata;
    Shared<Texture> _texture;

    Font(const char *path, int size);
    ~Font();

    void get_text_size(const char *text, int *width, int *height);

    Vec2i get_text_mesh(const char *text, float x, float y, std::vector<float> &vertices, std::vector<float> &uvs);
};