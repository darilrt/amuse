#pragma once

#include "engine/graphics/gfx.hpp"
#include "types.hpp"

class Shader
{
public:
    gfx::Pipeline pipeline;

    static Shared<Shader> from_files(const char *vertex_path, const char *fragment_path);
};