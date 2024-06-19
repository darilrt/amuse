#pragma once

#include "engine/graphics/texture.hpp"
#include "types.hpp"

extern Shared<Texture> icons_texture;
extern float icon_size;

void load_icons_texture();

#define ICON_FOLDER (void *)icons_texture->image.id, ImVec2(icon_size, icon_size), ImVec2(0.0, 1.0), ImVec2(0.5, 0.0)

#define ICON_OBJECT (void *)icons_texture->image.id, ImVec2(icon_size, icon_size), ImVec2(0.5, 1.0), ImVec2(1.0, 0.0)
