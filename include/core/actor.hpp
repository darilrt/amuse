#pragma once

#include <vector>
#include <filesystem>

#include "core/component.hpp"
#include "types.hpp"
#include "dll.hpp"

class Actor
{
public:
    std::string name;

    std::vector<Shared<Component>> components;
    Shared<Actor> parent;
    std::vector<Shared<Actor>> children;

    AMUSE_API void start();

    AMUSE_API void update();

    AMUSE_API Shared<Actor> load(const std::filesystem::path &path);
};