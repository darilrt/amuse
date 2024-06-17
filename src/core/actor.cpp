#include "logger.hpp"
#include "core/actor.hpp"

#include <toml.hpp>

void Actor::start()
{
    for (auto &component : components)
    {
        component->on_start();
    }

    for (auto &child : children)
    {
        child->start();
    }
}

void Actor::update()
{
    for (auto &component : components)
    {
        component->on_update();
    }

    for (auto &child : children)
    {
        child->update();
    }
}

Shared<Actor> Actor::load(const std::filesystem::path &path)
{
    auto data = toml::parse(path.string());

    Shared<Actor> actor = new_shared<Actor>();
    actor->name = toml::find<std::string>(data, "name");

    return actor;
}